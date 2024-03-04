import serial
import time
import sys
import signal
from subprocess import Popen, PIPE
import threading
import pandas as pd
import uuid
import pyautogui
import pyttsx3



pyautogui.FAILSAFE = False
DEVICE = 'COM7'


class FYALMDController:
    def __init__(self, num_measurements, fw_name, complexity, run_fw_test, program_name, fullscreen_option, out_folder) -> None:
        self.da_schmatzer = pyttsx3.init()
        #self.da_schmatzer.setProperty('rate', 120)
        self.num_measurements = int(num_measurements)
        self.threshold = 0
        self.fw_name = fw_name
        self.complexity = complexity
        self.run_fw_test = False if run_fw_test == 'False' else True
        self.program_name = program_name
        self.is_fullscreen = fullscreen_option == 'fullscreen'
        self.fullscreen_mode = None
        self.out_path = f"data/{out_folder}/{fw_name}_{complexity}_{run_fw_test}_{program_name}_{fullscreen_option}_{uuid.uuid4()}.csv"
        self.measuring = False
        self.latency_tester_process = None
        self.last_fw_latency = -1
        self.yalmd = None
        self.new_value = False
        self.measurements = []
        self.read_latency_tester_thread = threading.Thread(target=self.init_fw_latency_tester, daemon=True)


    def ensure_focus(self):
        time.sleep(0.2)
        pyautogui.moveTo(300, 300)
        time.sleep(0.2)
        self.yalmd.write('o'.encode())
        time.sleep(0.5)
        self.yalmd.write('o'.encode())
        time.sleep(0.5)
        self.yalmd.write('o'.encode())
        time.sleep(0.5)
        self.yalmd.write('o'.encode())


    def calibrate_yalmd(self):
        self.yalmd = serial.Serial(DEVICE)
        self.yalmd.flushInput()
        self.ensure_focus()
        time.sleep(5)  
        self.yalmd.write('c'.encode())
        yalmd_answer_byte = self.yalmd.readline()
        calibtration_answer = str(yalmd_answer_byte)
        self.threshold = calibtration_answer.split(': ')[-1] # todod: test!
        #decoded_answer_bytes = yalmd_answer_byte[0:len(yalmd_answer_byte)-2].decode("utf-8").split('#')
        

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


    # init pixel reader
    def init_fw_latency_tester(self):
        cmd = ['python', '-u', f'.\pixel_readers\{self.program_name}.py'] if 'y' in self.program_name else [f'.\pixel_readers\{self.program_name}.exe']
        self.latency_tester_process = Popen(cmd, stdout=PIPE, bufsize=1, universal_newlines=True)
        for line in self.latency_tester_process.stdout:
            if line.startswith('mode'):
                self.fullscreen_mode = line.split(':')[1].strip()
            else:
                self.last_fw_latency = int(line)
                self.new_value = True
                if self.measuring == False:
                    break
        self.latency_tester_process.kill()


    # make sure focus is in framework test applications and start pixel reader
    def start(self):
        self.ensure_focus()
        self.da_schmatzer.say(f'Ich teste jetzt {self.fw_name} {self.complexity} in {"fullscreen" if self.fullscreen_mode else "nicht fullscreen"} mit {self.program_name}.')
        self.da_schmatzer.runAndWait()
        self.measuring = True
        signal.signal(signal.SIGINT, signal_handler)
        if self.run_fw_test:
            self.read_latency_tester_thread.start()
        

    # stops measuring and terminates pixel reader process
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
        num_negative_diff = df[df['diff'] < 0].count().iloc[0]
        if num_negative_diff == 0:
            self.da_schmatzer.say(f'Ohhhhh yeah, keine negative Werte für {self.fw_name} {self.complexity} in {"fullscreen" if self.fullscreen_mode else "nicht fullscreen"} mit {self.program_name}')
            self.da_schmatzer.runAndWait()
        else:
            self.da_schmatzer.say(f'{str(num_negative_diff)} negative Werte für {self.fw_name} {self.complexity} in {"fullscreen" if self.fullscreen_mode else "nicht fullscreen"} mit {self.program_name}')
            self.da_schmatzer.runAndWait()


    # read yalmd's answer and pixel reader's answer
    def get_latency(self, iteration):
        ser_bytes = self.yalmd.readline()
        decoded_bytes = ser_bytes[0:len(ser_bytes)-2].decode("utf-8")
        if self.measuring:
            if self.run_fw_test:
                waiting_start = time.time()
                while not self.new_value:
                    if (time.time() - waiting_start) > 5:  
                       self.last_fw_latency = -1
                       self.da_schmatzer.say("Keinen Messwert erhalten.")
                       self.da_schmatzer.runAndWait()
                       break
            ete = int(decoded_bytes)
            diff = (ete - self.last_fw_latency)
            self.new_value = False
            self.measurements.append({'id': iteration, 
                                        'threshold': self.threshold,
                                        'framework': self.fw_name, 
                                        'complexity': self.complexity, 
                                        'framework_complexity': f'{self.fw_name}_{self.complexity}',
                                        'fullscreen': self.is_fullscreen,
                                        'fullscreen_mode': self.fullscreen_mode,
                                        'program': f'{self.program_name}',
                                        'fw_running': self.run_fw_test,
                                        'program_fwrunning': f'{self.program_name}_{self.run_fw_test}', 
                                        'ete': ete, 
                                        'fw': self.last_fw_latency, 
                                        'diff': diff
                                    })
            

    # make sure pixel reader windup has initializes its context before starting measurements
    def wait_for_windup_initialization(self):
        time.sleep(2.5)
        self.da_schmatzer.say("7 Sekunden sind vorbei!")
        self.da_schmatzer.runAndWait()
        self.yalmd.write('o'.encode())
        time.sleep(0.3)
        self.yalmd.write('o'.encode())
        time.sleep(4)
        self.da_schmatzer.say("Obacht! Gleich gehts los!")
        self.da_schmatzer.runAndWait()


    # measure <ITERATIONS>-times
    def measure(self):
        self.start()
        self.wait_for_windup_initialization()
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
if len(sys.argv) == 8:
    fyalmd_controller = FYALMDController(sys.argv[1], sys.argv[2], sys.argv[3], sys.argv[4], sys.argv[5], sys.argv[6], sys.argv[7])
    fyalmd_controller.calibrate_yalmd()
    time.sleep(3)  # to make sure framework tester has started
    fyalmd_controller.measure()
    fyalmd_controller.save_data()
    sys.exit(0)

print('arguments required: num_measurements, fw_name, complexity, run_fw_test, program_name, fullscreen_option, out_folder')
sys.exit(-1)
    