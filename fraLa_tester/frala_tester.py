import os
import time
import sys
import uuid
import random
import winsound
import threading
import pyautogui
import pandas as pd
from subprocess import Popen, PIPE

# otherwise, wont move mouse if it is out of screen area
pyautogui.FAILSAFE = False


class FraLaTester:
    def __init__(self, num_measurements, program_name, out_folder='./data', terminate=False):
        self.num_measurements = num_measurements
        self.program_name = program_name
        self.out_folder = out_folder
        self.terminate = terminate

        self.measuring = False
        self.new_value = False
        self.last_fw_latency = -1
        self.measurements = []
        self.latency_tester_process = None
        self.read_latency_tester_thread = threading.Thread(target=self.init_fw_latency_tester, daemon=True)


    def ensure_focus(self):
        print('please tab into your test application')
        print('starting in 5')
        time.sleep(1)
        print('starting in 4')
        time.sleep(1)
        print('starting in 3')
        time.sleep(1)
        print('starting in 2')
        time.sleep(1)
        print('starting in 1')
        time.sleep(1)
        pyautogui.moveTo(70, 70)
        time.sleep(0.5)
        pyautogui.mouseDown()
        time.sleep(0.1)
        pyautogui.mouseUp()
        time.sleep(0.5)
        pyautogui.mouseDown()
        time.sleep(0.1)
        pyautogui.mouseUp()


    # init pixel reader
    def init_fw_latency_tester(self):
        cmd = [f'.\programs\{self.program_name}.exe']
        self.latency_tester_process = Popen(cmd, stdout=PIPE, bufsize=1, universal_newlines=True)
        # read output of measurement program
        for line in self.latency_tester_process.stdout:
            self.last_fw_latency = int(line)
            self.new_value = True
            if self.measuring == False:
                break
        self.latency_tester_process.kill()


    # make sure focus is in framework test applications and start pixel reader
    def start(self):
        self.ensure_focus()
        self.measuring = True
        self.read_latency_tester_thread.start()
        print('waiting for measurement program to initialize...')
        time.sleep(5)
        

    # stops measuring and terminates pixel reader process
    def stop(self):
        self.measuring = False
        try:
            self.latency_tester_process.terminate()
            time.sleep(1)
            self.read_latency_tester_thread.join()
        except:
            pass
            

    def save_data(self):
        print(f'{self.num_measurements} conducted. Saving data...')
        if not os.path.exists(self.out_folder):
            os.makedirs(self.out_folder)
        df = pd.DataFrame(self.measurements)
        df.to_csv(f"{self.out_folder}/{self.program_name}_{uuid.uuid4()}.csv")
        winsound.Beep(500, 500)
        print('measurements finished. terminating...')


    def get_latency(self, iteration):
        waiting_start = time.time()
        pyautogui.mouseDown()
        time.sleep(0.1)
        pyautogui.mouseUp()
        while not self.new_value:
            if (time.time() - waiting_start) > 3:  
                self.last_fw_latency = -1
                print(f'Measurement program could not detect color change for iteration {iteration}. Writing -1 instead.')
                if self.terminate:
                    # stop measurements if cannot read pixel color value
                    self.measuring = False  
                break
            

        self.new_value = False
        self.measurements.append({'id': iteration, 'program': f'{self.program_name}', 'fw': self.last_fw_latency})
            

    def measure(self):
        self.start()
        print('measuring...')
        counter = 0
        while True:
            if counter >= self.num_measurements:
                self.measuring = False
                break
            time.sleep(random.randint(500, 1500) / 1000)
            try:
                self.get_latency(counter)
                counter += 1
            except Exception as e:
                print(e)
                break
        self.stop()



if __name__ == "__main__":

    fraLa = None
    
    if len(sys.argv) < 3:
        print('arguments required: num_measurements, program_name')
        print('optional arguments: out_path, terminate')
        print('terminating...')
        sys.exit(-1)

    if len(sys.argv) > 5:
        print('too many arguments')
        print('arguments required: num_measurements, program_name')
        print('optional arguments: out_path, terminate')
        print('terminating...')
        sys.exit(-1)

    try:
        iterations = int(sys.argv[1])
    except:
        print("input for 'iterations' has to be integer. terminating...")
        sys.exit(-1)

    if len(sys.argv) == 3:
        fraLa = FraLaTester(iterations, sys.argv[2])
        fraLa.measure()
        fraLa.save_data()
        sys.exit(0)

    if len(sys.argv) == 4:
        fraLa = FraLaTester(iterations, sys.argv[2], sys.argv[3])
        fraLa.measure()
        fraLa.save_data()
        sys.exit(0)

    if len(sys.argv) == 5:
        if (sys.argv[4] == 'True' or sys.argv[4] == 'true' or sys.argv[4] == '1'):
            terminate = True
        elif (sys.argv[4] == 'False' or sys.argv[4] == 'false' or sys.argv[4] == '0'):
            terminate = False
        else:
            print("input for 'terminate' needs to be convertable to boolean (true/false, 0/1). terminating...")
            sys.exit(-1)
        fraLa = FraLaTester(iterations, sys.argv[2], sys.argv[3], terminate)
        fraLa.measure()
        fraLa.save_data()
        sys.exit(0)
    