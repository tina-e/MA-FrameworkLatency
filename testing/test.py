# import pygetwindow as gw

# for window in gw.getAllWindows():
#     print(window)
#     if window.title == "framework":
#         window.activate()
#     elif window.title == "Windows PowerShell":
#         window.minimize()

import os
import shutil

from subprocess import Popen, PIPE
import threading

def move_files_with_prefix(source_folder, destination_folder, prefix):
    # Ensure the destination folder exists
    if not os.path.exists(destination_folder):
        os.makedirs(destination_folder)

    # List all files in the source folder
    files = os.listdir(source_folder)

    # Iterate through the files and move those with content starting with the specified prefix
    for file in files:
        source_path = os.path.join(source_folder, file)
        destination_path = os.path.join(destination_folder, file)

        with open(source_path, 'r') as f:
            first_line = f.readline().strip()

        if first_line.startswith(prefix):
            shutil.move(source_path, destination_path)
            print(f"Moved {file} to {destination_folder}")

# Replace these paths with your actual source and destination folder paths
source_folder_path = "./data/sdl_1112_480hz_55"
destination_folder_path = "./data/sdl_1112_480hz_55_error"
prefix_to_match = "-"

#move_files_with_prefix(source_folder_path, destination_folder_path, prefix_to_match)


# def init_fw_latency_tester_windup():
#         cmd = [f'..\pixel_readers\windup_errorout.exe']
#         latency_tester_process = Popen(cmd, stdout=PIPE, bufsize=1, universal_newlines=True)
#         print(latency_tester_process)
#         for line in latency_tester_process.stdout:
#             print(line)
#             try:
#                 last_fw_latency = int(line)
#             except:
#                 pass
            
#             new_value = True
#             #if measuring == False:
#             #    break
#         latency_tester_process.kill()

# init_fw_latency_tester_windup()


import serial
import time

ser = serial.Serial('COM7')  # open serial port
ser.flushInput()

time.sleep(5)

ser.write('c'.encode())

ser_bytes = ser.readline()
print(ser_bytes)
decoded_bytes = ser_bytes.decode("utf-8")
print(decoded_bytes)

ser.close()

time.sleep(2)

ser = serial.Serial('COM7')  # open serial port
ser.flushInput()

for i in range(100):
    ser.write('m'.encode())
    ser_bytes = ser.readline()
    print(ser_bytes)
    decoded_bytes = ser_bytes.decode("utf-8")
    print(decoded_bytes)
    time.sleep(1)