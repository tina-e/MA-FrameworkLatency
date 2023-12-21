from ctypes import windll
import time
import win32api
import sys
import signal


def signal_handler(signal, frame):
    sys.exit(0)

def main():
    dc= windll.user32.GetDC(0)
    state = win32api.GetKeyState(0x01)
    while True:
        current_state = win32api.GetKeyState(0x01)
        if current_state != state and current_state >= 0:  # click detected
            state = current_state
            start = time.time()
            while tuple(int.to_bytes(windll.gdi32.GetPixel(dc, 5, 5), 3, "little"))[0] != 255:
                time.sleep(0.001)
            end = time.time()
            print(int((end - start) * 1000 * 1000))


#if __name__ == '__main__':
signal.signal(signal.SIGTERM, signal_handler)
signal.signal(signal.SIGINT, signal_handler)
main()