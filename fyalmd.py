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
        if (program_name == 'autoit_reader'):
            self.read_latency_tester_thread = threading.Thread(target=self.init_fw_latency_tester_autoit, daemon=True)
        elif (program_name == 'windup' or program_name == 'windup_test' or program_name == 'windup_errorout'):
            self.read_latency_tester_thread = threading.Thread(target=self.init_fw_latency_tester_windup, daemon=True)
        elif (program_name == 'windup_python' or program_name == 'ctypes_reader' or program_name == 'pyautogui_reader'):
            self.read_latency_tester_thread = threading.Thread(target=self.init_fw_latency_tester_py_extern, daemon=True)
        else:
            self.read_latency_tester_thread = threading.Thread(target=self.init_fw_latency_tester, daemon=True)


    def ensure_focus(self):
        try:
            for window in gw.getAllWindows():
                if window.title == "framework":
                    window.activate()
                elif window.title == "Windows PowerShell":
                    window.minimize()
        except:
            pass
        time.sleep(1)
        pyautogui.moveTo(300, 300)
        time.sleep(1)
        pyautogui.click()
        time.sleep(0.5)
        pyautogui.click()
        time.sleep(0.5)
        pyautogui.click()
        time.sleep(1)


    def calibrate_yalmd(self):
        self.ensure_focus()
        self.yalmd = serial.Serial('COM7')
        self.yalmd.flushInput()
        time.sleep(5)
        self.yalmd.write('c'.encode())
        yalmd_answer_byte = self.yalmd.readline()
        print(yalmd_answer_byte)
        #decoded_answer_bytes = yalmd_answer_byte[0:len(yalmd_answer_byte)-2].decode("utf-8")
        decoded_answer_bytes = yalmd_answer_byte[0:len(yalmd_answer_byte)-2].decode("utf-8")
        print(decoded_answer_bytes)
        #self.yalmd.close()
        #self.yalmd = None


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


    def init_fw_latency_tester_py_extern(self):
        cmd = ['python', '-u', f'.\pixel_readers\{self.program_name}.py']
        self.latency_tester_process = Popen(cmd, stdout=PIPE, bufsize=1, universal_newlines=True)
        for line in self.latency_tester_process.stdout:
            self.last_fw_latency = int(line)
            self.new_value = True
            if self.measuring == False:
                break
        self.latency_tester_process.kill()
        

    def init_fw_latency_tester_autoit(self):
        cmd = ['AutoIt3.exe', f'.\pixel_readers\{self.program_name}.au3']
        self.latency_tester_process = Popen(cmd, stdout=PIPE, bufsize=1, universal_newlines=True)
        for line in self.latency_tester_process.stdout:
            self.last_fw_latency = int(line)
            self.new_value = True
            if self.measuring == False:
                break
        self.latency_tester_process.kill()


    def init_fw_latency_tester(self):
        cmd = [f'.\pixel_readers\{self.program_name}\cmake-build-debug\{self.program_name}.exe']
        self.latency_tester_process = Popen(cmd, stdout=PIPE, bufsize=1, universal_newlines=True)
        for line in self.latency_tester_process.stdout:
            self.last_fw_latency = int(line)
            self.new_value = True
            if self.measuring == False:
                break
        self.latency_tester_process.kill()


    def init_fw_latency_tester_windup(self):
        cmd = [f'.\pixel_readers\{self.program_name}.exe']
        self.latency_tester_process = Popen(cmd, stdout=PIPE, bufsize=1, universal_newlines=True)
        for line in self.latency_tester_process.stdout:
            self.last_fw_latency = int(line)
            self.new_value = True
            if self.measuring == False:
                break
        self.latency_tester_process.kill()


    def start(self):
        self.ensure_focus()
        #self.yalmd = serial.Serial('COM7')
        self.measuring = True
        #self.yalmd.flushInput()
        signal.signal(signal.SIGINT, signal_handler)
        if self.run_fw_test:
            self.read_latency_tester_thread.start()
        time.sleep(1)
        

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
        print(ser_bytes)
        decoded_bytes = ser_bytes[0:len(ser_bytes)-1].decode("utf-8")
        print("result: " + decoded_bytes)
        if self.measuring:
            if self.run_fw_test:
                #waiting_start = time.time()
                while not self.new_value:
                    #print("waiting")
                    pass
                    # time.sleep(0.000001) # sleep 1 us
                    # if there is no new value after 5sec, break and append -1 for fw latency
                    # if (time.time() - waiting_start) > 5:  
                    #    self.last_fw_latency = -1
                    #    break
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


if len(sys.argv) == 2:
    if sys.argv[1] == 'calibrate':
        fyalmd_controller = FYALMDController(None, None, None, None, None, None)
        fyalmd_controller.calibrate_yalmd()
        sys.exit(0)

elif len(sys.argv) == 8:
    if sys.argv[1] == 'calibrate_and_measure':
        fyalmd_controller = FYALMDController(sys.argv[2], sys.argv[3], sys.argv[4], sys.argv[5], sys.argv[6], sys.argv[7])
        fyalmd_controller.calibrate_yalmd()
        time.sleep(1)
        fyalmd_controller.measure()
        fyalmd_controller.save_data()
        sys.exit(0)
    elif sys.argv[1] == 'measure':
        fyalmd_controller = FYALMDController(sys.argv[2], sys.argv[3], sys.argv[4], sys.argv[5], sys.argv[6], sys.argv[7])
        time.sleep(1)
        fyalmd_controller.measure()
        fyalmd_controller.save_data()
        sys.exit(0)

print('arguments required: action, num_measurements, fw_name, complexity, run_fw_test, program_name, out_folder')
sys.exit(-1)
    