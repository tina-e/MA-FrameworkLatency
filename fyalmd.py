import serial
import time
import sys
import signal
from subprocess import Popen, PIPE
import threading
import pandas as pd
import uuid
import pyautogui
import pygetwindow as gw


pyautogui.FAILSAFE = False
DEVICE = 'COM7'


class FYALMDController:
    def __init__(self, num_measurements, fw_name, complexity, run_fw_test, program_name, out_folder) -> None:
        self.num_measurements = int(num_measurements)
        self.fw_name = fw_name
        self.complexity = complexity
        self.run_fw_test = False if run_fw_test == 'False' else True
        self.program_name = program_name
        self.out_path = f"data/{out_folder}/{fw_name}_{complexity}_{run_fw_test}_{program_name}_{uuid.uuid4()}.csv"
        self.measuring = False
        self.latency_tester_process = None
        self.last_fw_latency = -1
        self.yalmd = None
        self.new_value = False
        self.measurements = []
        self.read_latency_tester_thread = threading.Thread(target=self.init_fw_latency_tester, daemon=True)


    def ensure_focus(self):
        # try:
        #     for window in gw.getAllWindows():
        #         if window.title == "framework":
        #             window.activate()
        #         elif window.title == "Windows PowerShell":
        #             window.minimize()
        # except:
        #     pass
        time.sleep(1)
        pyautogui.moveTo(300, 300)
        time.sleep(1)
        self.yalmd.write('o'.encode())
        time.sleep(1)
        self.yalmd.write('o'.encode())
        # for i in range(3):
        #     pyautogui.click()
        #     time.sleep(0.5)


    def calibrate_yalmd(self):
        self.yalmd = serial.Serial(DEVICE)
        self.yalmd.flushInput()
        self.ensure_focus()
        time.sleep(5)  
        self.yalmd.write('c'.encode())
        yalmd_answer_byte = self.yalmd.readline()
        decoded_answer_bytes = yalmd_answer_byte[0:len(yalmd_answer_byte)-1].decode("utf-8")
        print(decoded_answer_bytes)


    ## to start windup_python without extern script
    # def init_fw_latency_tester_py(self):
    #     device = d3dshot.create(capture_output="numpy")
    #     state = win32api.GetKeyState(0x01)
    #     while True:
    #         current_state = win32api.GetKeyState(0x01)
    #         if current_state != state and current_state >= 0:  # click detected
    #             start = time.time()
    #             while device.screenshot(region=(0, 0, 1, 1))[0][0][0] != 255:
    #                 continue
    #             self.last_fw_latency = int((time.time() - start) * 1000000)
    #         if self.measuring == False:
    #             break


    def init_fw_latency_tester(self):
        if (self.program_name == 'windup' or self.program_name == 'windup_test'):
            cmd = [f'.\pixel_readers\{self.program_name}.exe']
        elif (self.program_name == 'windup_python' or self.program_name == 'ctypes_reader' or self.program_name == 'pyautogui_reader'):
            cmd = ['python', '-u', f'.\pixel_readers\{self.program_name}.py']
        else:
            cmd = [f'.\pixel_readers\{self.program_name}\cmake-build-debug\{self.program_name}.exe']

        self.latency_tester_process = Popen(cmd, stdout=PIPE, bufsize=1, universal_newlines=True)
        for line in self.latency_tester_process.stdout:
            self.last_fw_latency = int(line)
            self.new_value = True
            if self.measuring == False:
                break
        self.latency_tester_process.kill()



    def start(self):
        self.ensure_focus()
        self.measuring = True
        signal.signal(signal.SIGINT, signal_handler)
        if self.run_fw_test:
            self.read_latency_tester_thread.start()
        

    def stop(self):
        self.measuring = False
        self.yalmd.close()
        self.yalmd = None

        if self.run_fw_test:
            try:
                self.latency_tester_process.terminate()
                time.sleep(1)
                self.read_latency_tester_thread.join()
            except:
                pass
            

    def save_data(self):
        df = pd.DataFrame(self.measurements)
        df.to_csv(self.out_path)


    def get_latency(self, iteration):
        ser_bytes = self.yalmd.readline()
        decoded_bytes = ser_bytes[0:len(ser_bytes)-1].decode("utf-8")
        if self.measuring:
            if self.run_fw_test:
                waiting_start = time.time()
                while not self.new_value:
                    # print("waiting")
                    # pass
                    # time.sleep(0.000001) # sleep 1 us
                    # if there is no new value after 5sec, break and append -1 for fw latency
                    if (time.time() - waiting_start) > 5:  
                       self.last_fw_latency = -1
                       break
            ete = int(decoded_bytes)
            diff = (ete - self.last_fw_latency)
            self.new_value = False
            self.measurements.append({'id': iteration, 
                                        'framework': self.fw_name, 
                                        'complexity': self.complexity, 
                                        'framework_complexity': f'{self.fw_name}_{self.complexity}',
                                        'program': f'{self.program_name}',
                                        'fw_running': self.run_fw_test,
                                        'program_fwrunning': f'{self.program_name}_{self.run_fw_test}', 
                                        'ete': ete, 
                                        'fw': self.last_fw_latency, 
                                        'diff': diff
                                    })
 
    def measure(self):
        self.start()
        time.sleep(2)
        self.yalmd.write('o'.encode())
        time.sleep(0.1)
        self.yalmd.write('o'.encode())
        time.sleep(4)
        counter = 0
        while True:
            if counter < self.num_measurements:
                self.yalmd.write('m'.encode())
            else:
                self.measuring = False
                break

            try:
                self.get_latency(counter)
                counter += 1
            except Exception as e:
                print(e)
                break
        self.stop()




fyalmd_controller = None


def signal_handler(sig, frame):
    if fyalmd_controller:
        fyalmd_controller.stop()
        time.sleep(1)
    sys.exit(0)

print(sys.argv)
if len(sys.argv) == 7:
    fyalmd_controller = FYALMDController(sys.argv[1], sys.argv[2], sys.argv[3], sys.argv[4], sys.argv[5], sys.argv[6])
    fyalmd_controller.calibrate_yalmd()
    time.sleep(5)  # to make sure framework tester is ready steady go 
    fyalmd_controller.measure()
    fyalmd_controller.save_data()
    sys.exit(0)


print('arguments required: num_measurements, fw_name, complexity, run_fw_test, program_name, out_folder')
sys.exit(-1)
    