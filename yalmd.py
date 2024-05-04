import serial
import time
import os

DEVICE = 'COM7'

time.sleep(7)

# switch to framework, click one or two times to ensure focus

yalmd = serial.Serial(DEVICE)
yalmd.flushInput()

yalmd.write('c'.encode())
yalmd_answer_byte = yalmd.readline()
calibtration_answer = str(yalmd_answer_byte)
threshold = calibtration_answer.split(': ')[-1].strip().split('\\')[0]
print(threshold)

time.sleep(5)

print("started at: " + time.time())
for i in range(220):
    yalmd.write('m'.encode())

os._exit(0)
