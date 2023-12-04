import d3dshot
import time
import win32api
import sys
import pandas
import signal

# import pygetwindow as gw

# try:
#     for window in gw.getWindowsWithTitle("framework"):
#         print(window)
#         if window.title == "framework":
#             window.activate()
#             window.maximize()
# except:
#     pass

click_timestamps = []

def signal_handler(signal, frame):
    print("signal windup")
    df = pandas.DataFrame(data={"windup_python": click_timestamps})
    df.to_csv("../data/clicks/windup_python.csv", sep=',',index=False)
    sys.exit(0)

def main():
    device = d3dshot.create(capture_output="numpy")
    state = win32api.GetKeyState(0x01)
    while True:
        current_state = win32api.GetKeyState(0x01)
        if current_state != state and current_state >= 0:  # click detected
            state = current_state
            start = time.time()
            click_timestamps.append(start)
            # #while True:
            # test = device.screenshot(region=(5, 5, 6, 6))
            # print(test)
            #     #if test[0][0][0] == 255:
            #     #    break
            while device.screenshot(region=(5, 5, 6, 6))[0][0][0] != 255:
                time.sleep(0.000001)
            end = time.time()
            print(int((end - start) * 1000 * 1000))


#if __name__ == '__main__':
signal.signal(signal.SIGTERM, signal_handler)
signal.signal(signal.SIGINT, signal_handler)
main()