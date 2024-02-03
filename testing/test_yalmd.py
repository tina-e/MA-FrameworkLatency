import serial
import time
import sys
import signal

yalmd = serial.Serial('COM8')
yalmd.flushInput()

time.sleep(5)

yalmd.write('c'.encode())

yalmd_answer_byte = yalmd.readline()
decoded_answer_bytes = yalmd_answer_byte[0:len(yalmd_answer_byte)-2].decode("utf-8")
print(decoded_answer_bytes)

for i in range(10):
    yalmd.write('m'.encode())
    yalmd_answer_byte = yalmd.readline()
    decoded_answer_bytes = yalmd_answer_byte[0:len(yalmd_answer_byte)-2].decode("utf-8")
    print(decoded_answer_bytes)
    time.sleep(1)

yalmd.close()
