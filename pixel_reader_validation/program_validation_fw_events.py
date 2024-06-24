import csv
import time
import os, sys
import threading
from subprocess import Popen, PIPE
import pyautogui
pyautogui.FAILSAFE = False

PROGRAMS = ['getpixel', 'bitblt', 'getdbits', 'windup']
TEST_APPS = ['GLEW_SDL', 'SDL2_OpenGL']
# COMMANDS_PROGRAMS = [[f'./{PROGRAMS[0]}.exe'], [f'./{PROGRAMS[1]}.exe'], [f'./{PROGRAMS[2]}.exe'], [f'./{PROGRAMS[3]}.exe']]
# COMMANDS_TEST_APPS = [[f'./test_apps/{TEST_APPS[0]}.exe'], [f'./test_apps/{TEST_APPS[1]}.exe'], [f'./test_apps/{TEST_APPS[2]}.exe']]
DATA_DIR = 'data/final_'


def start_test_app(test_app):
    return Popen([f'./test_apps/{test_app}.exe'], stdout=PIPE, bufsize=1, universal_newlines=True)


def ensure_focus():
    time.sleep(3)
    pyautogui.click()
    time.sleep(1)
    pyautogui.click()


def read_test_app_out():
    for line in process_test_app.stdout:
        #print(line)
        output_test_app.append(line)


def start_measurement_program(program):
        return Popen([f'./programs/{program}.exe'], stdout=PIPE, bufsize=1, universal_newlines=True)


def save(program, test_app):
    data = []
    for line in output_program:
        splitted_line = line.strip().split(':')
        data.append([splitted_line[0], splitted_line[1], splitted_line[2]])
    print(data)
    with open(f'{DATA_DIR}_{test_app}_{program}_program.csv', 'w') as f:
        write = csv.writer(f)   
        write.writerow(['event_type', 'timestamp', 'color_equal'])
        write.writerows(data)
    data = []
    for line in output_test_app:
        splitted_line = line.strip().split(':')
        data.append([splitted_line[0], splitted_line[1], splitted_line[2]])
    print(data)
    with open(f'{DATA_DIR}_{test_app}_{program}_app.csv', 'w') as f:
        write = csv.writer(f)   
        write.writerow(['event_type', 'color_value', 'timestamp'])
        write.writerows(data)


for test_app in TEST_APPS:
    for program in PROGRAMS:
    
        output_test_app = []
        process_test_app = start_test_app(test_app)

        ensure_focus()

        # start thread for reading test app output
        tester_app_thread = threading.Thread(target=read_test_app_out, daemon=True)
        tester_app_thread.start()

        # ensure focus again, just to be sure
        time.sleep(1.5)
        pyautogui.click()

        # start measurement program
        output_program = []
        process_program = start_measurement_program(program)

        # read output of measurement program data
        for line in process_program.stdout:
            print(line)
            if process_test_app.poll() != None:
                tester_app_thread.join()
                process_program.kill()
                save(program, test_app)
                break
            else:
                output_program.append(line)

        












