import pandas as pd
import pyautogui
import serial
import time
import sys


DEVICE = 'COM7'
ITERATIONS = sys.argv[1]
FRAMEWORK = sys.argv[2]
PATH = sys.argv[3]


# open connection
vsync_tester = serial.Serial(DEVICE)
vsync_tester.flushInput()


# ensure focus
pyautogui.moveTo(30, 30)
time.sleep(1)
vsync_tester.write('o'.encode())
time.sleep(0.3)
vsync_tester.write('o'.encode())
time.sleep(0.7)
vsync_tester.write('o'.encode())
time.sleep(0.3)
vsync_tester.write('o'.encode())
time.sleep(1)


# start vsync checking
refresh_results = []
for i in range(ITERATIONS):
    vsync_tester.write('v'.encode())  
    # should return...
    # ... 0 if top is refreshed before bottom
    # ... 1 if bottom is refreshed before top
    yalmd_answer_byte = vsync_tester.readline()
    decoded_answer_bytes = yalmd_answer_byte[0:len(yalmd_answer_byte)-2].decode("utf-8")
    refresh_results.append(int(decoded_answer_bytes))
    time.sleep(1)  # maybe brauchts das nicht, je nach dem, wie dort gecoded

# close connection
vsync_tester.close()


# preprocess data
if len(refresh_results) != ITERATIONS:
    if len(refresh_results) > ITERATIONS:
        refresh_results = refresh_results[:ITERATIONS]
    elif len(refresh_results) < ITERATIONS:
        refresh_results = refresh_results + [None] * (ITERATIONS - len(refresh_results))
                                                      
# save data
data = pd.read_csv(PATH, index_col=False)
if FRAMEWORK not in data.columns:
    data[FRAMEWORK] = refresh_results
else:
    data[f'{FRAMEWORK}_{time.time()}'] = refresh_results
data.to_csv(PATH)

