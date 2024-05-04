import csv
import time
import os, sys
from subprocess import Popen, PIPE
import pyautogui
pyautogui.FAILSAFE = False

DATA_DIR = 'program_validation_0405_home_test_long.csv'
PROGRAMS = ['getpixel', 'bitblt', 'getdbits', 'windup']

# start test app
command_test_app = [f'./test_app_2.exe']
process_test_app = Popen(command_test_app, stdout=PIPE, bufsize=1, universal_newlines=True)

# ensure focus
time.sleep(3)
pyautogui.click()

# start measurement program
command_program = [f'./{PROGRAMS[0]}.exe']
process_program = Popen(command_program, stdout=PIPE, bufsize=1, universal_newlines=True)

# for line in process_test_app.stdout:
#     print(line)

def save(lines):
    data = []
    for line in lines:
        splitted_line = line.strip().split(':')
        data.append([splitted_line[0], splitted_line[1]])
    print(data)
    with open(DATA_DIR, 'w') as f:
        write = csv.writer(f)   
        write.writerow(['event_type', 'timestamp'])
        write.writerows(data)


# read measurement program data
lines = []
for line in process_program.stdout:
    if process_test_app.poll() != None:
        process_program.kill()
        save(lines)
        break
    else:
        lines.append(line)







