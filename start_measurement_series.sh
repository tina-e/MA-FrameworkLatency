#!/bin/sh

ITERATIONS=50
DATA_DIR="windup"

mkdir "./data/$DATA_DIR"

#killall -9 picom

# ACTION=$1
# ITERATIONS=$2
# TEST_PROGRAM=$3
# TEST_COMPLEXITY=$4
# FW_RUNNING=$5
# PIXEL_READER=$6
# DATA_DIR=$7

sleep "5s"

# ./start_measurements_sep.sh calibrate_and_measure $ITERATIONS Qt5 default True getpixel $DATA_DIR
# ./start_measurements_sep.sh measure $ITERATIONS Qt5 default False getpixel $DATA_DIR
# ./start_measurements_sep.sh measure $ITERATIONS Qt5 default True getdbits $DATA_DIR
# ./start_measurements_sep.sh measure $ITERATIONS Qt5 default False getdbits $DATA_DIR
# ./start_measurements_sep.sh measure $ITERATIONS Qt5 default True bitblt $DATA_DIR
# ./start_measurements_sep.sh measure $ITERATIONS Qt5 default False bitblt $DATA_DIR
# ./start_measurements_sep.sh measure $ITERATIONS Qt5 rects True getpixel $DATA_DIR
# ./start_measurements_sep.sh measure $ITERATIONS Qt5 rects False getpixel $DATA_DIR
# ./start_measurements_sep.sh measure $ITERATIONS Qt5 rects True getdbits $DATA_DIR
# ./start_measurements_sep.sh measure $ITERATIONS Qt5 rects False getdbits $DATA_DIR
# ./start_measurements_sep.sh measure $ITERATIONS Qt5 rects True bitblt $DATA_DIR
# ./start_measurements_sep.sh measure $ITERATIONS Qt5 rects False bitblt $DATA_DIR

./start_measurements_sep.sh calibrate_and_measure $ITERATIONS Qt5 default True windup $DATA_DIR
./start_measurements_sep.sh measure $ITERATIONS Qt5 default False windup $DATA_DIR
./start_measurements_sep.sh measure $ITERATIONS Qt5 rects True windup $DATA_DIR
./start_measurements_sep.sh measure $ITERATIONS Qt5 rects False windup $DATA_DIR

# ./start_measurements_sep.sh measure $ITERATIONS Qt6 default True getpixel $DATA_DIR
# ./start_measurements_sep.sh measure $ITERATIONS Qt6 default False getpixel $DATA_DIR
# ./start_measurements_sep.sh measure $ITERATIONS Qt6 default True getdbits $DATA_DIR
# ./start_measurements_sep.sh measure $ITERATIONS Qt6 default False getdbits $DATA_DIR
# ./start_measurements_sep.sh measure $ITERATIONS Qt6 default True bitblt $DATA_DIR
# ./start_measurements_sep.sh measure $ITERATIONS Qt6 default False bitblt $DATA_DIR
# ./start_measurements_sep.sh measure $ITERATIONS Qt6 rects True getpixel $DATA_DIR
# ./start_measurements_sep.sh measure $ITERATIONS Qt6 rects False getpixel $DATA_DIR
# ./start_measurements_sep.sh measure $ITERATIONS Qt6 rects True getdbits $DATA_DIR
# ./start_measurements_sep.sh measure $ITERATIONS Qt6 rects False getdbits $DATA_DIR
# ./start_measurements_sep.sh measure $ITERATIONS Qt6 rects True bitblt $DATA_DIR
# ./start_measurements_sep.sh measure $ITERATIONS Qt6 rects False bitblt $DATA_DIR

./start_measurements_sep.sh measure $ITERATIONS Qt6 default True windup $DATA_DIR
./start_measurements_sep.sh measure $ITERATIONS Qt6 default False windup $DATA_DIR
./start_measurements_sep.sh measure $ITERATIONS Qt6 rects True windup $DATA_DIR
./start_measurements_sep.sh measure $ITERATIONS Qt6 rects False windup $DATA_DIR

# ./start_measurements_sep.sh measure $ITERATIONS DirectX11 default True getpixel $DATA_DIR
# ./start_measurements_sep.sh measure $ITERATIONS DirectX11 default False getpixel $DATA_DIR
# ./start_measurements_sep.sh measure $ITERATIONS DirectX11 default True getdbits $DATA_DIR
# ./start_measurements_sep.sh measure $ITERATIONS DirectX11 default False getdbits $DATA_DIR
# ./start_measurements_sep.sh measure $ITERATIONS DirectX11 default True bitblt $DATA_DIR
# ./start_measurements_sep.sh measure $ITERATIONS DirectX11 default False bitblt $DATA_DIR
# ./start_measurements_sep.sh measure $ITERATIONS DirectX11 rects True getpixel $DATA_DIR
# ./start_measurements_sep.sh measure $ITERATIONS DirectX11 rects False getpixel $DATA_DIR
# ./start_measurements_sep.sh measure $ITERATIONS DirectX11 rects True getdbits $DATA_DIR
# ./start_measurements_sep.sh measure $ITERATIONS DirectX11 rects False getdbits $DATA_DIR
# ./start_measurements_sep.sh measure $ITERATIONS DirectX11 rects True bitblt $DATA_DIR
# ./start_measurements_sep.sh measure $ITERATIONS DirectX11 rects False bitblt $DATA_DIR

./start_measurements_sep.sh measure $ITERATIONS DirectX11 default True windup $DATA_DIR
./start_measurements_sep.sh measure $ITERATIONS DirectX11 default False windup $DATA_DIR
./start_measurements_sep.sh measure $ITERATIONS DirectX11 rects True windup $DATA_DIR
./start_measurements_sep.sh measure $ITERATIONS DirectX11 rects False windup $DATA_DIR


# # SDL2 ---------------------------------------------------------------------------------------
# ./start_measurement.sh calibrate_and_measure $ITERATIONS SDL2_Software default True getpixel $DATA_DIR
# ./start_measurement.sh measure $ITERATIONS SDL2_Software default False getpixel $DATA_DIR
# ./start_measurement.sh calibrate_and_measure $ITERATIONS SDL2_Software default True windup_python $DATA_DIR
# ./start_measurement.sh measure $ITERATIONS SDL2_Software default False windup_python $DATA_DIR
# ./start_measurement.sh measure $ITERATIONS SDL2_Software default True bitblt $DATA_DIR
# ./start_measurement.sh measure $ITERATIONS SDL2_Software default False bitblt $DATA_DIR
# ./start_measurement.sh measure $ITERATIONS SDL2_Software default True getdbits $DATA_DIR
# ./start_measurement.sh measure $ITERATIONS SDL2_Software default False getdbits $DATA_DIR

./start_measurements_sep.sh measure $ITERATIONS SDL2_Software default True windup $DATA_DIR
./start_measurements_sep.sh measure $ITERATIONS SDL2_Software default False windup $DATA_DIR
./start_measurements_sep.sh measure $ITERATIONS SDL2_Software rects True windup $DATA_DIR
./start_measurements_sep.sh measure $ITERATIONS SDL2_Software rects False windup $DATA_DIR

# ./start_measurement.sh measure $ITERATIONS SDL2_OPENGL default True getpixel $DATA_DIR
# ./start_measurement.sh measure $ITERATIONS SDL2_OPENGL default False getpixel $DATA_DIR
# ./start_measurement.sh measure $ITERATIONS SDL2_OPENGL default True bitblt $DATA_DIR
# ./start_measurement.sh measure $ITERATIONS SDL2_OPENGL default False bitblt $DATA_DIR
# ./start_measurement.sh measure $ITERATIONS SDL2_OPENGL default True getdbits $DATA_DIR
# ./start_measurement.sh measure $ITERATIONS SDL2_OPENGL default False getdbits $DATA_DIR
# ./start_measurement.sh calibrate_and_measure $ITERATIONS SDL2_OPENGL default True windup_python $DATA_DIR
# ./start_measurement.sh measure $ITERATIONS SDL2_OPENGL default False windup_python $DATA_DIR

./start_measurements_sep.sh measure $ITERATIONS SDL2_OPENGL default True windup $DATA_DIR
./start_measurements_sep.sh measure $ITERATIONS SDL2_OPENGL default False windup $DATA_DIR
./start_measurements_sep.sh measure $ITERATIONS SDL2_OPENGL rects True windup $DATA_DIR
./start_measurements_sep.sh measure $ITERATIONS SDL2_OPENGL rects False windup $DATA_DIR

# ./start_measurement.sh measure $ITERATIONS SDL2_OpenGLES default True getpixel $DATA_DIR
# ./start_measurement.sh measure $ITERATIONS SDL2_OpenGLES default False getpixel $DATA_DIR
# ./start_measurement.sh measure $ITERATIONS SDL2_OpenGLES default True bitblt $DATA_DIR
# ./start_measurement.sh measure $ITERATIONS SDL2_OpenGLES default False bitblt $DATA_DIR
# ./start_measurement.sh measure $ITERATIONS SDL2_OpenGLES default True getdbits $DATA_DIR
# ./start_measurement.sh measure $ITERATIONS SDL2_OpenGLES default False getdbits $DATA_DIR
# ./start_measurement.sh measure $ITERATIONS SDL2_OpenGLES default True windup_python $DATA_DIR
# ./start_measurement.sh measure $ITERATIONS SDL2_OpenGLES default False windup_python $DATA_DIR

./start_measurements_sep.sh measure $ITERATIONS SDL2_OpenGLES default True windup $DATA_DIR
./start_measurements_sep.sh measure $ITERATIONS SDL2_OpenGLES default False windup $DATA_DIR
./start_measurements_sep.sh measure $ITERATIONS SDL2_OpenGLES rects True windup $DATA_DIR
./start_measurements_sep.sh measure $ITERATIONS SDL2_OpenGLES rects False windup $DATA_DIR

# ./start_measurement.sh measure $ITERATIONS SDL2_Software rects True getpixel $DATA_DIR
# ./start_measurement.sh measure $ITERATIONS SDL2_Software rects False getpixel $DATA_DIR
# ./start_measurement.sh measure $ITERATIONS SDL2_Software rects True windup_python $DATA_DIR
# ./start_measurement.sh measure $ITERATIONS SDL2_Software rects False windup_python $DATA_DIR
# ./start_measurement.sh measure $ITERATIONS SDL2_Software rects True bitblt $DATA_DIR
# ./start_measurement.sh measure $ITERATIONS SDL2_Software rects False bitblt $DATA_DIR
# ./start_measurement.sh measure $ITERATIONS SDL2_Software rects True getdbits $DATA_DIR
# ./start_measurement.sh measure $ITERATIONS SDL2_Software rects False getdbits $DATA_DIR

# ./start_measurement.sh measure $ITERATIONS SDL2_OPENGL rects True getpixel $DATA_DIR
# ./start_measurement.sh measure $ITERATIONS SDL2_OPENGL rects False getpixel $DATA_DIR
# ./start_measurement.sh measure $ITERATIONS SDL2_OPENGL rects True bitblt $DATA_DIR
# ./start_measurement.sh measure $ITERATIONS SDL2_OPENGL rects False bitblt $DATA_DIR
# ./start_measurement.sh measure $ITERATIONS SDL2_OPENGL rects True getdbits $DATA_DIR
# ./start_measurement.sh measure $ITERATIONS SDL2_OPENGL rects False getdbits $DATA_DIR
# ./start_measurement.sh measure $ITERATIONS SDL2_OPENGL rects True windup_python $DATA_DIR
# ./start_measurement.sh measure $ITERATIONS SDL2_OPENGL rects False windup_python $DATA_DIR

# ./start_measurement.sh measure $ITERATIONS SDL2_OpenGLES rects True getpixel $DATA_DIR
# ./start_measurement.sh measure $ITERATIONS SDL2_OpenGLES rects False getpixel $DATA_DIR
# ./start_measurement.sh measure $ITERATIONS SDL2_OpenGLES rects True bitblt $DATA_DIR
# ./start_measurement.sh measure $ITERATIONS SDL2_OpenGLES rects False bitblt $DATA_DIR
# ./start_measurement.sh measure $ITERATIONS SDL2_OpenGLES rects True getdbits $DATA_DIR
# ./start_measurement.sh measure $ITERATIONS SDL2_OpenGLES rects False getdbits $DATA_DIR
# ./start_measurement.sh measure $ITERATIONS SDL2_OpenGLES rects True windup_python $DATA_DIR
# ./start_measurement.sh measure $ITERATIONS SDL2_OpenGLES rects False windup_python $DATA_DIR


# # # pygame ---------------------------------------------------------------------------------------
# ./start_measurement.sh calibrate_and_measure $ITERATIONS pygame default True autoit_reader $DATA_DIR
# ./start_measurement.sh measure $ITERATIONS pygame default False autoit_reader $DATA_DIR
# ./start_measurement.sh measure $ITERATIONS pygame rects True autoit_reader $DATA_DIR
# ./start_measurement.sh measure $ITERATIONS pygame rects False autoit_reader $DATA_DIR

# ./start_measurement.sh calibrate_and_measure $ITERATIONS pygame default True ctypes_reader $DATA_DIR
# ./start_measurement.sh measure $ITERATIONS pygame default False ctypes_reader $DATA_DIR
# ./start_measurement.sh measure $ITERATIONS pygame rects True ctypes_reader $DATA_DIR
# ./start_measurement.sh measure $ITERATIONS pygame rects False ctypes_reader $DATA_DIR

# ./start_measurement.sh measure $ITERATIONS pygame default True pyautogui_reader $DATA_DIR
# ./start_measurement.sh measure $ITERATIONS pygame default False pyautogui_reader $DATA_DIR
# ./start_measurement.sh measure $ITERATIONS pygame rects True pyautogui_reader $DATA_DIR
# ./start_measurement.sh measure $ITERATIONS pygame rects False pyautogui_reader $DATA_DIR

# ./start_measurement.sh measure $ITERATIONS pygame default True windup_python $DATA_DIR
# ./start_measurement.sh measure $ITERATIONS pygame default False windup_python $DATA_DIR
# ./start_measurement.sh measure $ITERATIONS pygame rects True windup_python $DATA_DIR
# ./start_measurement.sh measure $ITERATIONS pygame rects False windup_python $DATA_DIR
# # ----------
#./start_measurement.sh calibrate_and_measure $ITERATIONS pygame default True windup_python $DATA_DIR
# ./start_measurement.sh measure $ITERATIONS pygame default False windup_python $DATA_DIR
# ./start_measurement.sh measure $ITERATIONS pygame default True getpixel $DATA_DIR
# ./start_measurement.sh measure $ITERATIONS pygame default False getpixel $DATA_DIR
# ./start_measurement.sh measure $ITERATIONS pygame default True bitblt $DATA_DIR
# ./start_measurement.sh measure $ITERATIONS pygame default False bitblt $DATA_DIR
# ./start_measurement.sh measure $ITERATIONS pygame default True getdbits $DATA_DIR
# ./start_measurement.sh measure $ITERATIONS pygame default False getdbits $DATA_DIR

# ./start_measurement.sh measure $ITERATIONS pygame rects True windup_python $DATA_DIR
# ./start_measurement.sh measure $ITERATIONS pygame rects False windup_python $DATA_DIR
# ./start_measurement.sh measure $ITERATIONS pygame rects True getpixel $DATA_DIR
# ./start_measurement.sh measure $ITERATIONS pygame rects False getpixel $DATA_DIR
# ./start_measurement.sh measure $ITERATIONS pygame rects True bitblt $DATA_DIR
# ./start_measurement.sh measure $ITERATIONS pygame rects False bitblt $DATA_DIR
# ./start_measurement.sh measure $ITERATIONS pygame rects True getdbits $DATA_DIR
# ./start_measurement.sh measure $ITERATIONS pygame rects False getdbits $DATA_DIR

./start_measurements_sep.sh measure $ITERATIONS pygame default True windup $DATA_DIR
./start_measurements_sep.sh measure $ITERATIONS pygame default False windup $DATA_DIR
./start_measurements_sep.sh measure $ITERATIONS pygame rects True windup $DATA_DIR
./start_measurements_sep.sh measure $ITERATIONS pygame rects False windup $DATA_DIR

# # wxpython ---------------------------------------------------------------------------------------
# ./start_measurement.sh calibrate_and_measure $ITERATIONS wxpython default True windup_python $DATA_DIR
# ./start_measurement.sh measure $ITERATIONS wxpython default False windup_python $DATA_DIR
# ./start_measurement.sh measure $ITERATIONS wxpython default True getpixel $DATA_DIR
# ./start_measurement.sh measure $ITERATIONS wxpython default False getpixel $DATA_DIR
# ./start_measurement.sh measure $ITERATIONS wxpython default True bitblt $DATA_DIR
# ./start_measurement.sh measure $ITERATIONS wxpython default False bitblt $DATA_DIR
# ./start_measurement.sh measure $ITERATIONS wxpython default True getdbits $DATA_DIR
# ./start_measurement.sh measure $ITERATIONS wxpython default False getdbits $DATA_DIR

# ./start_measurement.sh calibrate_and_measure $ITERATIONS wxpython rects True windup_python $DATA_DIR
# ./start_measurement.sh measure $ITERATIONS wxpython rects False windup_python $DATA_DIR
# ./start_measurement.sh measure $ITERATIONS wxpython rects True getpixel $DATA_DIR
# ./start_measurement.sh measure $ITERATIONS wxpython rects False getpixel $DATA_DIR
# ./start_measurement.sh measure $ITERATIONS wxpython rects True bitblt $DATA_DIR
# ./start_measurement.sh measure $ITERATIONS wxpython rects False bitblt $DATA_DIR
# ./start_measurement.sh measure $ITERATIONS wxpython rects True getdbits $DATA_DIR
# ./start_measurement.sh measure $ITERATIONS wxpython rects False getdbits $DATA_DIR

# ./start_measurement.sh measure $ITERATIONS wxpython default True autoit_reader $DATA_DIR
# ./start_measurement.sh measure $ITERATIONS wxpython default False autoit_reader $DATA_DIR
# ./start_measurement.sh measure $ITERATIONS wxpython rects True autoit_reader $DATA_DIR
# ./start_measurement.sh measure $ITERATIONS wxpython rects False autoit_reader $DATA_DIR

./start_measurements_sep.sh measure $ITERATIONS wxpython default True windup $DATA_DIR
./start_measurements_sep.sh measure $ITERATIONS wxpython default False windup $DATA_DIR
./start_measurements_sep.sh measure $ITERATIONS wxpython rects True windup $DATA_DIR
./start_measurements_sep.sh measure $ITERATIONS wxpython rects False windup $DATA_DIR



# # # pyqt5 ---------------------------------------------------------------------------------------
# ./start_measurement.sh calibrate_and_measure $ITERATIONS pyqt5 default True windup_python $DATA_DIR
# ./start_measurement.sh measure $ITERATIONS pyqt5 default False windup_python $DATA_DIR
# ./start_measurement.sh calibrate_and_measure $ITERATIONS pyqt5 default True getpixel $DATA_DIR
# ./start_measurement.sh measure $ITERATIONS pyqt5 default False getpixel $DATA_DIR
# ./start_measurement.sh measure $ITERATIONS pyqt5 default True bitblt $DATA_DIR
# ./start_measurement.sh measure $ITERATIONS pyqt5 default False bitblt $DATA_DIR
# ./start_measurement.sh measure $ITERATIONS pyqt5 default True getdbits $DATA_DIR
# ./start_measurement.sh measure $ITERATIONS pyqt5 default False getdbits $DATA_DIR

# # ./start_measurement.sh measure $ITERATIONS pyqt5 rects True windup_python $DATA_DIR
# # ./start_measurement.sh measure $ITERATIONS pyqt5 rects False windup_python $DATA_DIR
# ./start_measurement.sh measure $ITERATIONS pyqt5 rects True getpixel $DATA_DIR
# ./start_measurement.sh measure $ITERATIONS pyqt5 rects False getpixel $DATA_DIR
# ./start_measurement.sh measure $ITERATIONS pyqt5 rects True bitblt $DATA_DIR
# ./start_measurement.sh measure $ITERATIONS pyqt5 rects False bitblt $DATA_DIR
# ./start_measurement.sh measure $ITERATIONS pyqt5 rects True getdbits $DATA_DIR
# ./start_measurement.sh measure $ITERATIONS pyqt5 rects False getdbits $DATA_DIR

./start_measurements_sep.sh measure $ITERATIONS pyqt5 default True windup $DATA_DIR
./start_measurements_sep.sh measure $ITERATIONS pyqt5 default False windup $DATA_DIR
./start_measurements_sep.sh measure $ITERATIONS pyqt5 rects True windup $DATA_DIR
./start_measurements_sep.sh measure $ITERATIONS pyqt5 rects False windup $DATA_DIR

# ./start_measurement.sh measure $ITERATIONS pyqt5 default True autoit_reader $DATA_DIR
# ./start_measurement.sh measure $ITERATIONS pyqt5 default False autoit_reader $DATA_DIR
# ./start_measurement.sh measure $ITERATIONS pyqt5 rects True autoit_reader $DATA_DIR
# ./start_measurement.sh measure $ITERATIONS pyqt5 rects False autoit_reader $DATA_DIR

# ./start_measurement.sh measure $ITERATIONS pyqt5 default True ctypes_reader $DATA_DIR
# ./start_measurement.sh measure $ITERATIONS pyqt5 default False ctypes_reader $DATA_DIR
# ./start_measurement.sh measure $ITERATIONS pyqt5 rects True ctypes_reader $DATA_DIR
# ./start_measurement.sh measure $ITERATIONS pyqt5 rects False ctypes_reader $DATA_DIR

# ./start_measurement.sh measure $ITERATIONS pyqt5 default True pyautogui_reader $DATA_DIR
# ./start_measurement.sh measure $ITERATIONS pyqt5 default False pyautogui_reader $DATA_DIR
# ./start_measurement.sh measure $ITERATIONS pyqt5 rects True pyautogui_reader $DATA_DIR
# ./start_measurement.sh measure $ITERATIONS pyqt5 rects False pyautogui_reader $DATA_DIR

# # # pyqt6 ---------------------------------------------------------------------------------------
# ./start_measurement.sh measure $ITERATIONS pyqt6 default True windup_python $DATA_DIR
# ./start_measurement.sh measure $ITERATIONS pyqt6 default False windup_python $DATA_DIR
# ./start_measurement.sh measure $ITERATIONS pyqt6 default True getpixel $DATA_DIR
# ./start_measurement.sh measure $ITERATIONS pyqt6 default False getpixel $DATA_DIR
# ./start_measurement.sh measure $ITERATIONS pyqt6 default True bitblt $DATA_DIR
# ./start_measurement.sh measure $ITERATIONS pyqt6 default False bitblt $DATA_DIR
# ./start_measurement.sh measure $ITERATIONS pyqt6 default True getdbits $DATA_DIR
# ./start_measurement.sh measure $ITERATIONS pyqt6 default False getdbits $DATA_DIR

# # ./start_measurement.sh calibrate_and_measure $ITERATIONS pyqt6 rects True windup_python $DATA_DIR
# # ./start_measurement.sh measure $ITERATIONS pyqt6 rects False windup_python $DATA_DIR
# ./start_measurement.sh measure $ITERATIONS pyqt6 rects True getpixel $DATA_DIR
# ./start_measurement.sh measure $ITERATIONS pyqt6 rects False getpixel $DATA_DIR
# ./start_measurement.sh measure $ITERATIONS pyqt6 rects True bitblt $DATA_DIR
# ./start_measurement.sh measure $ITERATIONS pyqt6 rects False bitblt $DATA_DIR
# ./start_measurement.sh measure $ITERATIONS pyqt6 rects True getdbits $DATA_DIR
# ./start_measurement.sh measure $ITERATIONS pyqt6 rects False getdbits $DATA_DIR

./start_measurements_sep.sh measure $ITERATIONS pyqt6 default True windup $DATA_DIR
./start_measurements_sep.sh measure $ITERATIONS pyqt6 default False windup $DATA_DIR
./start_measurements_sep.sh measure $ITERATIONS pyqt6 rects True windup $DATA_DIR
./start_measurements_sep.sh measure $ITERATIONS pyqt6 rects False windup $DATA_DIR

# ./start_measurement.sh measure $ITERATIONS pyqt6 default True autoit_reader $DATA_DIR
# ./start_measurement.sh measure $ITERATIONS pyqt6 default False autoit_reader $DATA_DIR
# ./start_measurement.sh measure $ITERATIONS pyqt6 rects True autoit_reader $DATA_DIR
# ./start_measurement.sh measure $ITERATIONS pyqt6 rects False autoit_reader $DATA_DIR

# ./start_measurement.sh measure $ITERATIONS pyqt6 default True ctypes_reader $DATA_DIR
# ./start_measurement.sh measure $ITERATIONS pyqt6 default False ctypes_reader $DATA_DIR
# ./start_measurement.sh measure $ITERATIONS pyqt6 rects True ctypes_reader $DATA_DIR
# ./start_measurement.sh measure $ITERATIONS pyqt6 rects False ctypes_reader $DATA_DIR

# ./start_measurement.sh measure $ITERATIONS pyqt6 default True pyautogui_reader $DATA_DIR
# ./start_measurement.sh measure $ITERATIONS pyqt6 default False pyautogui_reader $DATA_DIR
# ./start_measurement.sh measure $ITERATIONS pyqt6 rects True pyautogui_reader $DATA_DIR
# ./start_measurement.sh measure $ITERATIONS pyqt6 rects False pyautogui_reader $DATA_DIR

# # # tkinter ---------------------------------------------------------------------------------------
# ./start_measurement.sh measure $ITERATIONS tkinter default True windup_python $DATA_DIR
# ./start_measurement.sh measure $ITERATIONS tkinter default False windup_python $DATA_DIR
# ./start_measurement.sh measure $ITERATIONS tkinter default True getpixel $DATA_DIR
# ./start_measurement.sh measure $ITERATIONS tkinter default False getpixel $DATA_DIR
# ./start_measurement.sh measure $ITERATIONS tkinter default True bitblt $DATA_DIR
# ./start_measurement.sh measure $ITERATIONS tkinter default False bitblt $DATA_DIR
# ./start_measurement.sh measure $ITERATIONS tkinter default True getdbits $DATA_DIR
# ./start_measurement.sh measure $ITERATIONS tkinter default False getdbits $DATA_DIR

# # ./start_measurement.sh measure $ITERATIONS tkinter rects True windup_python $DATA_DIR
# # ./start_measurement.sh measure $ITERATIONS tkinter rects False windup_python $DATA_DIR
# ./start_measurement.sh measure $ITERATIONS tkinter rects True getpixel $DATA_DIR
# ./start_measurement.sh measure $ITERATIONS tkinter rects False getpixel $DATA_DIR
# ./start_measurement.sh measure $ITERATIONS tkinter rects True bitblt $DATA_DIR
# ./start_measurement.sh measure $ITERATIONS tkinter rects False bitblt $DATA_DIR
# ./start_measurement.sh measure $ITERATIONS tkinter rects True getdbits $DATA_DIR
# ./start_measurement.sh measure $ITERATIONS tkinter rects False getdbits $DATA_DIR

./start_measurements_sep.sh measure $ITERATIONS tkinter default True windup $DATA_DIR
./start_measurements_sep.sh measure $ITERATIONS tkinter default False windup $DATA_DIR
./start_measurements_sep.sh measure $ITERATIONS tkinter rects True windup $DATA_DIR
./start_measurements_sep.sh measure $ITERATIONS tkinter rects False windup $DATA_DIR

# ./start_measurement.sh measure $ITERATIONS tkinter default True autoit_reader $DATA_DIR
# ./start_measurement.sh measure $ITERATIONS tkinter default False autoit_reader $DATA_DIR
# ./start_measurement.sh measure $ITERATIONS tkinter rects True autoit_reader $DATA_DIR
# ./start_measurement.sh measure $ITERATIONS tkinter rects False autoit_reader $DATA_DIR

# ./start_measurement.sh measure $ITERATIONS tkinter default True ctypes_reader $DATA_DIR
# ./start_measurement.sh measure $ITERATIONS tkinter default False ctypes_reader $DATA_DIR
# ./start_measurement.sh measure $ITERATIONS tkinter rects True ctypes_reader $DATA_DIR
# ./start_measurement.sh measure $ITERATIONS tkinter rects False ctypes_reader $DATA_DIR

# ./start_measurement.sh measure $ITERATIONS tkinter default True pyautogui_reader $DATA_DIR
# ./start_measurement.sh measure $ITERATIONS tkinter default False pyautogui_reader $DATA_DIR
# ./start_measurement.sh measure $ITERATIONS tkinter rects True pyautogui_reader $DATA_DIR
# ./start_measurement.sh measure $ITERATIONS tkinter rects False pyautogui_reader $DATA_DIR


# # JavaSwing ---------------------------------------------------------------------------------------
# ./start_measurement.sh measure $ITERATIONS JavaSwing default True getpixel $DATA_DIR
# ./start_measurement.sh measure $ITERATIONS JavaSwing default False getpixel $DATA_DIR
# # ./start_measurement.sh measure $ITERATIONS JavaSwing default True windup_python $DATA_DIR
# # ./start_measurement.sh measure $ITERATIONS JavaSwing default False windup_python $DATA_DIR
# ./start_measurement.sh measure $ITERATIONS JavaSwing default True bitblt $DATA_DIR
# ./start_measurement.sh measure $ITERATIONS JavaSwing default False bitblt $DATA_DIR
# ./start_measurement.sh measure $ITERATIONS JavaSwing default True getdbits $DATA_DIR
# ./start_measurement.sh measure $ITERATIONS JavaSwing default False getdbits $DATA_DIR

# # ./start_measurement.sh measure $ITERATIONS JavaSwing rects True windup_python $DATA_DIR
# # ./start_measurement.sh measure $ITERATIONS JavaSwing rects False windup_python $DATA_DIR
# ./start_measurement.sh measure $ITERATIONS JavaSwing rects True getpixel $DATA_DIR
# ./start_measurement.sh measure $ITERATIONS JavaSwing rects False getpixel $DATA_DIR
# ./start_measurement.sh measure $ITERATIONS JavaSwing rects True bitblt $DATA_DIR
# ./start_measurement.sh measure $ITERATIONS JavaSwing rects False bitblt $DATA_DIR
# ./start_measurement.sh measure $ITERATIONS JavaSwing rects True getdbits $DATA_DIR
# ./start_measurement.sh measure $ITERATIONS JavaSwing rects False getdbits $DATA_DIR

./start_measurements_sep.sh measure $ITERATIONS JavaSwing default True windup $DATA_DIR
./start_measurements_sep.sh measure $ITERATIONS JavaSwing default False windup $DATA_DIR
./start_measurements_sep.sh measure $ITERATIONS JavaSwing rects True windup $DATA_DIR
./start_measurements_sep.sh measure $ITERATIONS JavaSwing rects False windup $DATA_DIR

# ./start_measurement.sh measure $ITERATIONS JavaSwing default True autoit_reader $DATA_DIR
# ./start_measurement.sh measure $ITERATIONS JavaSwing default False autoit_reader $DATA_DIR
# ./start_measurement.sh measure $ITERATIONS JavaSwing rects True autoit_reader $DATA_DIR
# ./start_measurement.sh measure $ITERATIONS JavaSwing rects False autoit_reader $DATA_DIR

# ./start_measurement.sh measure $ITERATIONS JavaSwing default True ctypes_reader $DATA_DIR
# ./start_measurement.sh measure $ITERATIONS JavaSwing default False ctypes_reader $DATA_DIR
# ./start_measurement.sh measure $ITERATIONS JavaSwing rects True ctypes_reader $DATA_DIR
# ./start_measurement.sh measure $ITERATIONS JavaSwing rects False ctypes_reader $DATA_DIR

# ./start_measurement.sh measure $ITERATIONS JavaSwing default True pyautogui_reader $DATA_DIR
# ./start_measurement.sh measure $ITERATIONS JavaSwing default False pyautogui_reader $DATA_DIR
# ./start_measurement.sh measure $ITERATIONS JavaSwing rects True pyautogui_reader $DATA_DIR
# ./start_measurement.sh measure $ITERATIONS JavaSwing rects False pyautogui_reader $DATA_DIR

# # Java2D ---------------------------------------------------------------------------------------
# ./start_measurement.sh measure $ITERATIONS Java2D default True windup_python $DATA_DIR
# ./start_measurement.sh measure $ITERATIONS Java2D default False windup_python $DATA_DIR
# ./start_measurement.sh measure $ITERATIONS Java2D default True getpixel $DATA_DIR
# ./start_measurement.sh measure $ITERATIONS Java2D default False getpixel $DATA_DIR
# ./start_measurement.sh measure $ITERATIONS Java2D default True bitblt $DATA_DIR
# ./start_measurement.sh measure $ITERATIONS Java2D default False bitblt $DATA_DIR
# ./start_measurement.sh measure $ITERATIONS Java2D default True getdbits $DATA_DIR
# ./start_measurement.sh measure $ITERATIONS Java2D default False getdbits $DATA_DIR

# # ./start_measurement.sh measure $ITERATIONS Java2D rects True windup_python $DATA_DIR
# # ./start_measurement.sh measure $ITERATIONS Java2D rects False windup_python $DATA_DIR
# ./start_measurement.sh measure $ITERATIONS Java2D rects True getpixel $DATA_DIR
# ./start_measurement.sh measure $ITERATIONS Java2D rects False getpixel $DATA_DIR
# ./start_measurement.sh measure $ITERATIONS Java2D rects True bitblt $DATA_DIR
# ./start_measurement.sh measure $ITERATIONS Java2D rects False bitblt $DATA_DIR
# ./start_measurement.sh measure $ITERATIONS Java2D rects True getdbits $DATA_DIR
# ./start_measurement.sh measure $ITERATIONS Java2D rects False getdbits $DATA_DIR

./start_measurements_sep.sh measure $ITERATIONS Java2D default True windup $DATA_DIR
./start_measurements_sep.sh measure $ITERATIONS Java2D default False windup $DATA_DIR
./start_measurements_sep.sh measure $ITERATIONS Java2D rects True windup $DATA_DIR
./start_measurements_sep.sh measure $ITERATIONS Java2D rects False windup $DATA_DIR

# ./start_measurement.sh measure $ITERATIONS Java2D default True autoit_reader $DATA_DIR
# ./start_measurement.sh measure $ITERATIONS Java2D default False autoit_reader $DATA_DIR
# ./start_measurement.sh measure $ITERATIONS Java2D rects True autoit_reader $DATA_DIR
# ./start_measurement.sh measure $ITERATIONS Java2D rects False autoit_reader $DATA_DIR

# ./start_measurement.sh measure $ITERATIONS Java2D default True ctypes_reader $DATA_DIR
# ./start_measurement.sh measure $ITERATIONS Java2D default False ctypes_reader $DATA_DIR
# ./start_measurement.sh measure $ITERATIONS Java2D rects True ctypes_reader $DATA_DIR
# ./start_measurement.sh measure $ITERATIONS Java2D rects False ctypes_reader $DATA_DIR

# ./start_measurement.sh measure $ITERATIONS Java2D default True pyautogui_reader $DATA_DIR
# ./start_measurement.sh measure $ITERATIONS Java2D default False pyautogui_reader $DATA_DIR
# ./start_measurement.sh measure $ITERATIONS Java2D rects True pyautogui_reader $DATA_DIR
# ./start_measurement.sh measure $ITERATIONS Java2D rects False pyautogui_reader $DATA_DIR

# # JavaFX ---------------------------------------------------------------------------------------
# ./start_measurements_sep.sh measure $ITERATIONS JavaFX default True windup $DATA_DIR
# ./start_measurements_sep.sh measure $ITERATIONS JavaFX default False windup $DATA_DIR
# ./start_measurements_sep.sh measure $ITERATIONS JavaFX rects True windup $DATA_DIR
# ./start_measurements_sep.sh measure $ITERATIONS JavaFX rects False windup $DATA_DIR



# # # # pyglet ---------------------------------------------------------------------------------------
# ./start_measurement.sh calibrate_and_measure $ITERATIONS pyglet default True windup_python $DATA_DIR
# ./start_measurement.sh measure $ITERATIONS pyglet default False windup_python $DATA_DIR
# ./start_measurement.sh measure $ITERATIONS pyglet default True getpixel $DATA_DIR
# ./start_measurement.sh measure $ITERATIONS pyglet default False getpixel $DATA_DIR
# ./start_measurement.sh measure $ITERATIONS pyglet default True bitblt $DATA_DIR
# ./start_measurement.sh measure $ITERATIONS pyglet default False bitblt $DATA_DIR
# ./start_measurement.sh measure $ITERATIONS pyglet default True getdbits $DATA_DIR
# ./start_measurement.sh measure $ITERATIONS pyglet default False getdbits $DATA_DIR

# # ./start_measurement.sh measure $ITERATIONS pyglet rects True windup_python $DATA_DIR
# # ./start_measurement.sh measure $ITERATIONS pyglet rects False windup_python $DATA_DIR
# ./start_measurement.sh measure $ITERATIONS pyglet rects True getpixel $DATA_DIR
# ./start_measurement.sh measure $ITERATIONS pyglet rects False getpixel $DATA_DIR
# ./start_measurement.sh measure $ITERATIONS pyglet rects True bitblt $DATA_DIR
# ./start_measurement.sh measure $ITERATIONS pyglet rects False bitblt $DATA_DIR
# ./start_measurement.sh measure $ITERATIONS pyglet rects True getdbits $DATA_DIR
# ./start_measurement.sh measure $ITERATIONS pyglet rects False getdbits $DATA_DIR

./start_measurements_sep.sh measure $ITERATIONS pyglet default True windup $DATA_DIR
./start_measurements_sep.sh measure $ITERATIONS pyglet default False windup $DATA_DIR
./start_measurements_sep.sh measure $ITERATIONS pyglet rects True windup $DATA_DIR
./start_measurements_sep.sh measure $ITERATIONS pyglet rects False windup $DATA_DIR

# ./start_measurement.sh measure $ITERATIONS pyglet default True autoit_reader $DATA_DIR
# ./start_measurement.sh measure $ITERATIONS pyglet default False autoit_reader $DATA_DIR
# ./start_measurement.sh measure $ITERATIONS pyglet rects True autoit_reader $DATA_DIR
# ./start_measurement.sh measure $ITERATIONS pyglet rects False autoit_reader $DATA_DIR

# ./start_measurement.sh measure $ITERATIONS pyglet default True ctypes_reader $DATA_DIR
# ./start_measurement.sh measure $ITERATIONS pyglet default False ctypes_reader $DATA_DIR
# ./start_measurement.sh measure $ITERATIONS pyglet rects True ctypes_reader $DATA_DIR
# ./start_measurement.sh measure $ITERATIONS pyglet rects False ctypes_reader $DATA_DIR

# ./start_measurement.sh measure $ITERATIONS pyglet default True pyautogui_reader $DATA_DIR
# ./start_measurement.sh measure $ITERATIONS pyglet default False pyautogui_reader $DATA_DIR
# ./start_measurement.sh measure $ITERATIONS pyglet rects True pyautogui_reader $DATA_DIR
# ./start_measurement.sh measure $ITERATIONS pyglet rects False pyautogui_reader $DATA_DIR

# # # # glut ---------------------------------------------------------------------------------------
# ./start_measurement.sh measure $ITERATIONS GLUT default True windup_python $DATA_DIR
# ./start_measurement.sh measure $ITERATIONS GLUT default False windup_python $DATA_DIR
# ./start_measurement.sh measure $ITERATIONS GLUT default True getpixel $DATA_DIR
# ./start_measurement.sh measure $ITERATIONS GLUT default False getpixel $DATA_DIR
# ./start_measurement.sh measure $ITERATIONS GLUT default True bitblt $DATA_DIR
# ./start_measurement.sh measure $ITERATIONS GLUT default False bitblt $DATA_DIR
# ./start_measurement.sh measure $ITERATIONS GLUT default True getdbits $DATA_DIR
# ./start_measurement.sh measure $ITERATIONS GLUT default False getdbits $DATA_DIR

# # ./start_measurement.sh measure $ITERATIONS GLUT rects True windup_python $DATA_DIR
# # ./start_measurement.sh measure $ITERATIONS GLUT rects False windup_python $DATA_DIR
# ./start_measurement.sh measure $ITERATIONS GLUT rects True getpixel $DATA_DIR
# ./start_measurement.sh measure $ITERATIONS GLUT rects False getpixel $DATA_DIR
# ./start_measurement.sh measure $ITERATIONS GLUT rects True bitblt $DATA_DIR
# ./start_measurement.sh measure $ITERATIONS GLUT rects False bitblt $DATA_DIR
# ./start_measurement.sh measure $ITERATIONS GLUT rects True getdbits $DATA_DIR
# ./start_measurement.sh measure $ITERATIONS GLUT rects False getdbits $DATA_DIR

./start_measurements_sep.sh measure $ITERATIONS GLUT default True windup $DATA_DIR
./start_measurements_sep.sh measure $ITERATIONS GLUT default False windup $DATA_DIR
./start_measurements_sep.sh measure $ITERATIONS GLUT rects True windup $DATA_DIR
./start_measurements_sep.sh measure $ITERATIONS GLUT rects False windup $DATA_DIR

# ./start_measurement.sh measure $ITERATIONS GLUT default True autoit_reader $DATA_DIR
# ./start_measurement.sh measure $ITERATIONS GLUT default False autoit_reader $DATA_DIR
# ./start_measurement.sh measure $ITERATIONS GLUT rects True autoit_reader $DATA_DIR
# ./start_measurement.sh measure $ITERATIONS GLUT rects False autoit_reader $DATA_DIR

# ./start_measurement.sh measure $ITERATIONS GLUT default True ctypes_reader $DATA_DIR
# ./start_measurement.sh measure $ITERATIONS GLUT default False ctypes_reader $DATA_DIR
# ./start_measurement.sh measure $ITERATIONS GLUT rects True ctypes_reader $DATA_DIR
# ./start_measurement.sh measure $ITERATIONS GLUT rects False ctypes_reader $DATA_DIR

# ./start_measurement.sh measure $ITERATIONS GLUT default True pyautogui_reader $DATA_DIR
# ./start_measurement.sh measure $ITERATIONS GLUT default False pyautogui_reader $DATA_DIR
# ./start_measurement.sh measure $ITERATIONS GLUT rects True pyautogui_reader $DATA_DIR
# ./start_measurement.sh measure $ITERATIONS GLUT rects False pyautogui_reader $DATA_DIR



# ./start_measurement.sh measure $ITERATIONS FLTK default True getpixel $DATA_DIR
# ./start_measurement.sh measure $ITERATIONS FLTK default False getpixel $DATA_DIR
# ./start_measurement.sh measure $ITERATIONS FLTK rects True getpixel $DATA_DIR
# ./start_measurement.sh measure $ITERATIONS FLTK rects False getpixel $DATA_DIR
# ./start_measurement.sh measure $ITERATIONS FLTK default True getdbits $DATA_DIR
# ./start_measurement.sh measure $ITERATIONS FLTK default False getdbits $DATA_DIR
# ./start_measurement.sh measure $ITERATIONS FLTK rects True getdbits $DATA_DIR
# ./start_measurement.sh measure $ITERATIONS FLTK rects False getdbits $DATA_DIR
# ./start_measurement.sh measure $ITERATIONS FLTK default True bitblt $DATA_DIR
# ./start_measurement.sh measure $ITERATIONS FLTK default False bitblt $DATA_DIR
# ./start_measurement.sh measure $ITERATIONS FLTK rects True bitblt $DATA_DIR
# ./start_measurement.sh measure $ITERATIONS FLTK rects False bitblt $DATA_DIR

./start_measurements_sep.sh measure $ITERATIONS FLTK default True windup $DATA_DIR
./start_measurements_sep.sh measure $ITERATIONS FLTK default False windup $DATA_DIR
./start_measurements_sep.sh measure $ITERATIONS FLTK rects True windup $DATA_DIR
./start_measurements_sep.sh measure $ITERATIONS FLTK rects False windup $DATA_DIR

# ./start_measurement.sh measure $ITERATIONS win32 default True getpixel $DATA_DIR
# ./start_measurement.sh measure $ITERATIONS win32 default False getpixel $DATA_DIR
# ./start_measurement.sh measure $ITERATIONS win32 rects True getpixel $DATA_DIR
# ./start_measurement.sh measure $ITERATIONS win32 rects False getpixel $DATA_DIR
# ./start_measurement.sh measure $ITERATIONS win32 default True getdbits $DATA_DIR
# ./start_measurement.sh measure $ITERATIONS win32 default False getdbits $DATA_DIR
# ./start_measurement.sh measure $ITERATIONS win32 rects True getdbits $DATA_DIR
# ./start_measurement.sh measure $ITERATIONS win32 rects False getdbits $DATA_DIR
# ./start_measurement.sh measure $ITERATIONS win32 default True bitblt $DATA_DIR
# ./start_measurement.sh measure $ITERATIONS win32 default False bitblt $DATA_DIR
# ./start_measurement.sh measure $ITERATIONS win32 rects True bitblt $DATA_DIR
# ./start_measurement.sh measure $ITERATIONS win32 rects False bitblt $DATA_DIR

./start_measurements_sep.sh measure $ITERATIONS win32 default True windup $DATA_DIR
./start_measurements_sep.sh measure $ITERATIONS win32 default False windup $DATA_DIR
./start_measurements_sep.sh measure $ITERATIONS win32 rects True windup $DATA_DIR
./start_measurements_sep.sh measure $ITERATIONS win32 rects False windup $DATA_DIR

# ./start_measurement.sh measure $ITERATIONS GLEW default True getpixel $DATA_DIR
# ./start_measurement.sh measure $ITERATIONS GLEW default False getpixel $DATA_DIR
# ./start_measurement.sh measure $ITERATIONS GLEW rects True getpixel $DATA_DIR
# ./start_measurement.sh measure $ITERATIONS GLEW rects False getpixel $DATA_DIR
# ./start_measurement.sh measure $ITERATIONS GLEW default True getdbits $DATA_DIR
# ./start_measurement.sh measure $ITERATIONS GLEW default False getdbits $DATA_DIR
# ./start_measurement.sh measure $ITERATIONS GLEW rects True getdbits $DATA_DIR
# ./start_measurement.sh measure $ITERATIONS GLEW rects False getdbits $DATA_DIR
# ./start_measurement.sh measure $ITERATIONS GLEW default True bitblt $DATA_DIR
# ./start_measurement.sh measure $ITERATIONS GLEW default False bitblt $DATA_DIR
# ./start_measurement.sh measure $ITERATIONS GLEW rects True bitblt $DATA_DIR
# ./start_measurement.sh measure $ITERATIONS GLEW rects False bitblt $DATA_DIR

./start_measurements_sep.sh measure $ITERATIONS GLEW default True windup $DATA_DIR
./start_measurements_sep.sh measure $ITERATIONS GLEW default False windup $DATA_DIR
./start_measurements_sep.sh measure $ITERATIONS GLEW rects True windup $DATA_DIR
./start_measurements_sep.sh measure $ITERATIONS GLEW rects False windup $DATA_DIR
