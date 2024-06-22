from subprocess import Popen, PIPE
import pyautogui
import time
import sys
import serial


DEVICE = 'COM3'
FRAMEWORK = sys.argv[1]
FULLSCREEN = sys.argv[2]
PATH = sys.argv[3]

# ensure focus
yalmd = serial.Serial(DEVICE)
yalmd.flushInput()
pyautogui.moveTo(30, 30)
time.sleep(1)
yalmd.write('o'.encode())
time.sleep(0.3)
yalmd.write('o'.encode())
time.sleep(0.7)
yalmd.write('o'.encode())
time.sleep(0.3)
yalmd.write('o'.encode())
time.sleep(2)
yalmd.close()

# open tester
cmd = './fullscreen_tester.exe'
notification_tester_process = Popen(cmd, stdout=PIPE, bufsize=1, universal_newlines=True)
for line in notification_tester_process.stdout:
    print(f'{FRAMEWORK} - {FULLSCREEN}: {line}')
    file = open(PATH, "a")
    file.write(f'{FRAMEWORK},{FULLSCREEN},{line}')
    file.close()

notification_tester_process.kill()
