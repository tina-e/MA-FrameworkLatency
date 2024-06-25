import csv
import time
import os, sys
import threading
import uuid
from subprocess import Popen, PIPE
import pyautogui
pyautogui.FAILSAFE = False

ITERATIONS = 1
PROGRAMS = ['getpixel', 'bitblt', 'getdbits', 'windup']
TEST_APPS = ['SDL2_OpenGL']
# COMMANDS_PROGRAMS = [[f'./{PROGRAMS[0]}.exe'], [f'./{PROGRAMS[1]}.exe'], [f'./{PROGRAMS[2]}.exe'], [f'./{PROGRAMS[3]}.exe']]
# COMMANDS_TEST_APPS = [[f'./test_apps/{TEST_APPS[0]}.exe'], [f'./test_apps/{TEST_APPS[1]}.exe'], [f'./test_apps/{TEST_APPS[2]}.exe']]
DATA_DIR = f'./data/final_60hz/'


def start_test_app(test_app):
    return Popen([f'./test_apps/{test_app}.exe'], stdout=PIPE, bufsize=1, universal_newlines=True)


def ensure_focus():
    time.sleep(2)
    pyautogui.click()
    time.sleep(1)
    pyautogui.click()
    time.sleep(2)


def read_test_app_out():
    for line in process_test_app.stdout:
        #print(line)
        output_test_app.append(line)


def start_measurement_program(program):
        return Popen([f'./programs/{program}.exe'], stdout=PIPE, bufsize=1, universal_newlines=True)


def save(program, test_app, iteration):
    data = []
    for line in output_program:
        splitted_line = line.strip().split(':')
        data.append([splitted_line[0], splitted_line[1], splitted_line[2], iteration])
    with open(f'{DATA_DIR}{test_app}_{program}_program_{iteration}.csv', 'w') as f:
        write = csv.writer(f)   
        write.writerow(['event_type', 'timestamp', 'color_equal', 'iteration'])
        write.writerows(data)
    data = []
    for line in output_test_app:
        splitted_line = line.strip().split(':')
        data.append([splitted_line[0], splitted_line[1], splitted_line[2], iteration])
    with open(f'{DATA_DIR}{test_app}_{program}_app_{iteration}.csv', 'w') as f:
        write = csv.writer(f)   
        write.writerow(['event_type', 'color_value', 'timestamp', 'iteration'])
        write.writerows(data)


for i in range(ITERATIONS):
    for test_app in TEST_APPS:
        for program in PROGRAMS:
        
            output_test_app = []
            process_test_app = start_test_app(test_app)

            # start thread for reading test app output
            tester_app_thread = threading.Thread(target=read_test_app_out, daemon=True)
            tester_app_thread.start()

            ensure_focus()

            # start measurement program
            output_program = []
            process_program = start_measurement_program(program)

            # start transition
            time.sleep(3)
            pyautogui.click()

            # read output of measurement program data
            for line in process_program.stdout:
                print(line)
                if process_test_app.poll() != None:
                    tester_app_thread.join()
                    process_program.kill()
                    save(program, test_app, i)
                    break
                else:
                    output_program.append(line)

            












