from subprocess import Popen, PIPE
import pyautogui
import time
import sys
import serial


DEVICE = 'COM7'
FRAMEWORK = sys.args(1)
FULLSCREEN = sys.args(2)


# todo: ensure focus
yalmd = serial.Serial(DEVICE)
yalmd.flushInput()
pyautogui.moveTo(300, 300)
time.sleep(1)
yalmd.write('o'.encode())
time.sleep(0.3)
yalmd.write('o'.encode())
time.sleep(0.7)
yalmd.write('o'.encode())
time.sleep(0.3)
yalmd.write('o'.encode())
time.sleep(0.7)
yalmd.close()


file = open("./data/fullscreen_states/testing_fullscreen_0403.csv", "w")
file.close()


# open tester
cmd = '.\notification_tester.exe'
notification_tester_process = Popen(cmd, stdout=PIPE, bufsize=1, universal_newlines=True)
for line in notification_tester_process.stdout:
    print(f'{FRAMEWORK} - {FULLSCREEN}: {line}')
    file = open("./data/fullscreen_states/testing_fullscreen_0403.csv", "a")
    file.write(f'{FRAMEWORK},{FULLSCREEN},{line}\n')
    file.close()

notification_tester_process.kill()
