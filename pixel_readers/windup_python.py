import d3dshot
import time
import win32api
import pygetwindow as gw

try:
    for window in gw.getWindowsWithTitle("framework"):
        if window.title == "framework":
            window.activate()
            window.maximize()
except:
    pass

device = d3dshot.create(capture_output="numpy")
state = win32api.GetKeyState(0x01)
while True:
    current_state = win32api.GetKeyState(0x01)
    if current_state != state and current_state >= 0:  # click detected
        state = current_state
        start = time.time()
        while device.screenshot(region=(0, 0, 1, 1))[0][0][0] != 255:
            time.sleep(0.000001)
        end = time.time()
        print(int((end - start) * 1000 * 1000))

