import csv
import time
import os, sys
import threading
from subprocess import Popen, PIPE
import pyautogui
pyautogui.FAILSAFE = False

DATA_DIR = 'data/setup_test_getdbits_60hz'
PROGRAMS = ['getpixel', 'bitblt', 'getdbits', 'windup']


# start test app
output_test_app = []
command_test_app = [f'./test_app_50ms.exe']
process_test_app = Popen(command_test_app, stdout=PIPE, bufsize=1, universal_newlines=True)

# ensure focus
time.sleep(3)
# pyautogui.mouseDown()
# time.sleep(0.2)
# pyautogui.mouseDown()
pyautogui.click()
time.sleep(1)
pyautogui.click()
# pyautogui.mouseDown()
# time.sleep(0.2)
# pyautogui.mouseDown()

# read output of test app
def read_test_app_out():
    for line in process_test_app.stdout:
        print(line)
        output_test_app.append(line)


tester_app_thread = threading.Thread(target=read_test_app_out, daemon=True)
tester_app_thread.start()

# ensure focus
time.sleep(1.5)
pyautogui.click()

# start measurement program
output_program = []
command_program = [f'./{PROGRAMS[2]}.exe']
process_program = Popen(command_program, stdout=PIPE, bufsize=1, universal_newlines=True)


# save result to csv
def save():
    data = []
    for line in output_program:
        splitted_line = line.strip().split(':')
        data.append([splitted_line[0], splitted_line[1], splitted_line[2]])
    print(data)
    with open(f'{DATA_DIR}_program.csv', 'w') as f:
        write = csv.writer(f)   
        write.writerow(['event_type', 'timestamp', 'color_equal'])
        write.writerows(data)
    data = []
    for line in output_test_app:
        splitted_line = line.strip().split(':')
        data.append([splitted_line[0], splitted_line[1], splitted_line[2]])
    print(data)
    with open(f'{DATA_DIR}_app.csv', 'w') as f:
        write = csv.writer(f)   
        write.writerow(['event_type', 'color_value', 'timestamp'])
        write.writerows(data)


# read output of measurement program data
for line in process_program.stdout:
    print(line)
    if process_test_app.poll() != None:
        tester_app_thread.join()
        process_program.kill()
        save()
        break
    else:
        output_program.append(line)







