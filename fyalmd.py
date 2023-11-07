import serial
import io
import time
import sys
import signal
from subprocess import Popen, PIPE, CalledProcessError
import threading
import numpy as np
import pandas as pd
import uuid


class FYALMDController:
    def __init__(self, num_measurements, fw_name, complexity, run_fw_test, program_name, out_folder) -> None:
        self.num_measurements = int(num_measurements)
        self.fw_name = fw_name
        self.complexity = complexity
        self.run_fw_test = False if run_fw_test == 'False' else True
        self.program_name = program_name
        self.out_path = f"data/{out_folder}/{uuid.uuid4()}.csv"
        self.measuring = False
        self.latency_tester_process = None
        self.last_fw_latency = 0
        self.yalmd = serial.Serial('COM6')
        self.read_latency_tester_thread = threading.Thread(target=self.init_fw_latency_tester, daemon=True)
        self.measurements = []


    def calibrate_yalmd(self):
        self.yalmd.flushInput()
        time.sleep(5)
        self.yalmd.write('c'.encode())
        yalmd_answer_byte = self.yalmd.readline()
        decoded_answer_bytes = yalmd_answer_byte[0:len(yalmd_answer_byte)-2].decode("utf-8")
        print(decoded_answer_bytes)


    def init_fw_latency_tester(self):
        cmd = [f'.\framework_tester\{self.program_name}\cmake-build-debug\{self.program_name}.exe']
        self.latency_tester_process = Popen(cmd, stdout=PIPE, bufsize=1, universal_newlines=True, shell=True)
        for line in self.latency_tester_process.stdout:
            self.last_fw_latency = int(line)
            if self.measuring == False:
                break
        self.latency_tester_process.kill()


    def start(self):
        self.measuring = True
        self.yalmd.flushInput()
        signal.signal(signal.SIGINT, signal_handler)
        if self.run_fw_test:
            self.read_latency_tester_thread.start()
        time.sleep(1)
        

    def stop(self):
        self.measuring = False
        self.yalmd.close()

        if self.run_fw_test:
            self.latency_tester_process.kill()
            #read_latency_tester_thread.join()


    def save_data(self):
        df = pd.DataFrame(self.measurements)
        df.to_csv(self.out_path)


    def get_latency(self, iteration):
        ser_bytes = self.yalmd.readline()
        decoded_bytes = ser_bytes[0:len(ser_bytes)-2].decode("utf-8")
        if self.measuring:
            ete = int(decoded_bytes)
            diff = (ete - self.last_fw_latency)
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
        time.sleep(3)
        fyalmd_controller.measure()
        fyalmd_controller.save_data()
        sys.exit(0)
    elif sys.argv[1] == 'measure':
        fyalmd_controller = FYALMDController(sys.argv[2], sys.argv[3], sys.argv[4], sys.argv[5], sys.argv[6], sys.argv[7])
        time.sleep(3)
        fyalmd_controller.measure()
        fyalmd_controller.save_data()
        sys.exit(0)

print('arguments required: action, num_measurements, fw_name, complexity, run_fw_test, program_name, out_folder')
sys.exit(-1)
    