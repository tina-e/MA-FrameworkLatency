# MA-FrameworkLatency


## Repo Structure

📁 **framework_tester**
<br>Includes test programs for different frameworks. Default (from black to hwite on click) and Rects (from black to 1000 random rects on click)
- GLUT
- (SDL2)
- SDL2_OpenGl
- SDL2_OpenGLES
- SDL2_Software
- Java2D
- JavaSwing
- pygame
- pyglet
- pyqt5
- tkinter
- wxpython
- glumpy (glfw, pyglet, qt, sdl/pygame)

📁 **pixel_readers**
<br>Includes programs which allow for reading a certain pixels's color. Recognizes a click and waits then for certain pixel to turn white. Measures time passed between these events.
- windows bitblt
- windows getdbits
- windows getpixel
- windows desktop duplication (based on directX, python bindings)

📁 **framework_tester_wip**
<br>Work in progress for further frameworks...

📁 **pixel_reader_wip**
<br>Work in progrress for further pixel readers...

📁 **data**: measurement data
<br>|___📁 glumpy: glumpy measurements
<br>|___📁 pilot: first few measurements
<br>|___📁 test: test measurements to make sure script is working

📁 **analysis**: notebooks for analysis of measurements
<br>|___📁 glumpy: analysis of glumpy measurements
<br>|___📁 other: analysis of non-glumpy measurements
<br>|___📁 test: just messing around

🗎 `fylamd.py`
<br>controlls yalmd, starts measurement and saves data

🗎 `start_measuremnet_glumpy.sh`
<br>starts measurement and `fyalmd` for a given pixel reader and glumpy as framework tester

🗎 `start_measurement_series_glumpy.sh`
<br>starts a measurement series with each of the available pixel readers for glumpy framework tester (with each of the available backends)

🗎 `start_measuremnet.sh`
<br>starts measurement and `fyalmd` for a given pixel reader and a given framework tester

🗎 `start_measurement_series.sh`
<br>starts a measurement series width each of the available pixel readers for each of the available framework testers (without glumpy)

🗎 `test.py`
<br>just messing around


<br><br>*Testers and Readers compiled for Windows 11.*

---
## Usage
For measurement series with glumpy:
- adjust number of iterations and directory for resulting data in `start_measurement_series_glumpy.sh`
- run `./start_measurement_series_glumpy.sh`
- just to be safe: minimize/close all windows which do not belong to measurements

For measurement series without glumpy:
- adjust number of iterations and directory for resulting data in `start_measurement_series.sh`
- run `./start_measurement_series.sh`
- just to be safe: minimize/close all windows which do not belong to measurements
---

## Required:
- Python 3.8
- pip packages
    - `pip install wxPython`
    - `pip install pyqt5`
    - `pip install pyqt6`
    - `pip install pygame`
    - `pip install pyglet`
    - `pip install Pillow`
    - `pip install d3dshot`
    - `pip install win32api`
    - `pip install pygetwindow`
    - `pip install pyautogui`
    - `pip install pandas`
    - `pip install numpy`
- `glumpy` as described here: https://glumpy.readthedocs.io/en/latest/installation.html
- download and place `.dll`s next to your python.exe:
    - `freeglut.dll` (https://freeglut.sourceforge.net/docs/install.php)
    - `SDL2.dll` (https://github.com/libsdl-org/SDL/releases/tag/release-2.28.5)






