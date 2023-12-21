#!/bin/sh

ITERATIONS=50
DATA_DIR="2112_python_readers"

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


# # # pygame ---------------------------------------------------------------------------------------
./start_measurement.sh calibrate_and_measure $ITERATIONS pygame default True ctypes_reader $DATA_DIR
./start_measurement.sh measure $ITERATIONS pygame default False ctypes_reader $DATA_DIR
./start_measurement.sh measure $ITERATIONS pygame rects True ctypes_reader $DATA_DIR
./start_measurement.sh measure $ITERATIONS pygame rects False ctypes_reader $DATA_DIR

./start_measurement.sh measure $ITERATIONS pygame default True pyautogui_reader $DATA_DIR
./start_measurement.sh measure $ITERATIONS pygame default False pyautogui_reader $DATA_DIR
./start_measurement.sh measure $ITERATIONS pygame rects True pyautogui_reader $DATA_DIR
./start_measurement.sh measure $ITERATIONS pygame rects False pyautogui_reader $DATA_DIR

./start_measurement.sh measure $ITERATIONS pygame default True windup_python $DATA_DIR
./start_measurement.sh measure $ITERATIONS pygame default False windup_python $DATA_DIR
./start_measurement.sh measure $ITERATIONS pygame rects True windup_python $DATA_DIR
./start_measurement.sh measure $ITERATIONS pygame rects False windup_python $DATA_DIR

# # wxpython ---------------------------------------------------------------------------------------
./start_measurement.sh measure $ITERATIONS wxpython default True ctypes_reader $DATA_DIR
./start_measurement.sh measure $ITERATIONS wxpython default False ctypes_reader $DATA_DIR
./start_measurement.sh measure $ITERATIONS wxpython rects True ctypes_reader $DATA_DIR
./start_measurement.sh measure $ITERATIONS wxpython rects False ctypes_reader $DATA_DIR

./start_measurement.sh measure $ITERATIONS wxpython default True pyautogui_reader $DATA_DIR
./start_measurement.sh measure $ITERATIONS wxpython default False pyautogui_reader $DATA_DIR
./start_measurement.sh measure $ITERATIONS wxpython rects True pyautogui_reader $DATA_DIR
./start_measurement.sh measure $ITERATIONS wxpython rects False pyautogui_reader $DATA_DIR

./start_measurement.sh measure $ITERATIONS wxpython default True windup_python $DATA_DIR
./start_measurement.sh measure $ITERATIONS wxpython default False windup_python $DATA_DIR
./start_measurement.sh measure $ITERATIONS wxpython rects True windup_python $DATA_DIR
./start_measurement.sh measure $ITERATIONS wxpython rects False windup_python $DATA_DIR

# # # pyqt5 ---------------------------------------------------------------------------------------
./start_measurement.sh measure $ITERATIONS pyqt5 default True ctypes_reader $DATA_DIR
./start_measurement.sh measure $ITERATIONS pyqt5 default False ctypes_reader $DATA_DIR
./start_measurement.sh measure $ITERATIONS pyqt5 rects True ctypes_reader $DATA_DIR
./start_measurement.sh measure $ITERATIONS pyqt5 rects False ctypes_reader $DATA_DIR

./start_measurement.sh measure $ITERATIONS pyqt5 default True pyautogui_reader $DATA_DIR
./start_measurement.sh measure $ITERATIONS pyqt5 default False pyautogui_reader $DATA_DIR
./start_measurement.sh measure $ITERATIONS pyqt5 rects True pyautogui_reader $DATA_DIR
./start_measurement.sh measure $ITERATIONS pyqt5 rects False pyautogui_reader $DATA_DIR

./start_measurement.sh measure $ITERATIONS pyqt5 default True windup_python $DATA_DIR
./start_measurement.sh measure $ITERATIONS pyqt5 default False windup_python $DATA_DIR
./start_measurement.sh measure $ITERATIONS pyqt5 rects True windup_python $DATA_DIR
./start_measurement.sh measure $ITERATIONS pyqt5 rects False windup_python $DATA_DIR

# # # pyqt6 ---------------------------------------------------------------------------------------
./start_measurement.sh measure $ITERATIONS pyqt6 default True ctypes_reader $DATA_DIR
./start_measurement.sh measure $ITERATIONS pyqt6 default False ctypes_reader $DATA_DIR
./start_measurement.sh measure $ITERATIONS pyqt6 rects True ctypes_reader $DATA_DIR
./start_measurement.sh measure $ITERATIONS pyqt6 rects False ctypes_reader $DATA_DIR

./start_measurement.sh measure $ITERATIONS pyqt6 default True pyautogui_reader $DATA_DIR
./start_measurement.sh measure $ITERATIONS pyqt6 default False pyautogui_reader $DATA_DIR
./start_measurement.sh measure $ITERATIONS pyqt6 rects True pyautogui_reader $DATA_DIR
./start_measurement.sh measure $ITERATIONS pyqt6 rects False pyautogui_reader $DATA_DIR

./start_measurement.sh measure $ITERATIONS pyqt6 default True windup_python $DATA_DIR
./start_measurement.sh measure $ITERATIONS pyqt6 default False windup_python $DATA_DIR
./start_measurement.sh measure $ITERATIONS pyqt6 rects True windup_python $DATA_DIR
./start_measurement.sh measure $ITERATIONS pyqt6 rects False windup_python $DATA_DIR

# # # tkinter ---------------------------------------------------------------------------------------
./start_measurement.sh measure $ITERATIONS tkinter default True ctypes_reader $DATA_DIR
./start_measurement.sh measure $ITERATIONS tkinter default False ctypes_reader $DATA_DIR
./start_measurement.sh measure $ITERATIONS tkinter rects True ctypes_reader $DATA_DIR
./start_measurement.sh measure $ITERATIONS tkinter rects False ctypes_reader $DATA_DIR

./start_measurement.sh measure $ITERATIONS tkinter default True pyautogui_reader $DATA_DIR
./start_measurement.sh measure $ITERATIONS tkinter default False pyautogui_reader $DATA_DIR
./start_measurement.sh measure $ITERATIONS tkinter rects True pyautogui_reader $DATA_DIR
./start_measurement.sh measure $ITERATIONS tkinter rects False pyautogui_reader $DATA_DIR

./start_measurement.sh measure $ITERATIONS tkinter default True windup_python $DATA_DIR
./start_measurement.sh measure $ITERATIONS tkinter default False windup_python $DATA_DIR
./start_measurement.sh measure $ITERATIONS tkinter rects True windup_python $DATA_DIR
./start_measurement.sh measure $ITERATIONS tkinter rects False windup_python $DATA_DIR


# # JavaSwing ---------------------------------------------------------------------------------------
./start_measurement.sh measure $ITERATIONS JavaSwing default True ctypes_reader $DATA_DIR
./start_measurement.sh measure $ITERATIONS JavaSwing default False ctypes_reader $DATA_DIR
./start_measurement.sh measure $ITERATIONS JavaSwing rects True ctypes_reader $DATA_DIR
./start_measurement.sh measure $ITERATIONS JavaSwing rects False ctypes_reader $DATA_DIR

./start_measurement.sh measure $ITERATIONS JavaSwing default True pyautogui_reader $DATA_DIR
./start_measurement.sh measure $ITERATIONS JavaSwing default False pyautogui_reader $DATA_DIR
./start_measurement.sh measure $ITERATIONS JavaSwing rects True pyautogui_reader $DATA_DIR
./start_measurement.sh measure $ITERATIONS JavaSwing rects False pyautogui_reader $DATA_DIR

./start_measurement.sh measure $ITERATIONS JavaSwing default True windup_python $DATA_DIR
./start_measurement.sh measure $ITERATIONS JavaSwing default False windup_python $DATA_DIR
./start_measurement.sh measure $ITERATIONS JavaSwing rects True windup_python $DATA_DIR
./start_measurement.sh measure $ITERATIONS JavaSwing rects False windup_python $DATA_DIR

# # Java2D ---------------------------------------------------------------------------------------
./start_measurement.sh measure $ITERATIONS Java2D default True ctypes_reader $DATA_DIR
./start_measurement.sh measure $ITERATIONS Java2D default False ctypes_reader $DATA_DIR
./start_measurement.sh measure $ITERATIONS Java2D rects True ctypes_reader $DATA_DIR
./start_measurement.sh measure $ITERATIONS Java2D rects False ctypes_reader $DATA_DIR

./start_measurement.sh measure $ITERATIONS Java2D default True pyautogui_reader $DATA_DIR
./start_measurement.sh measure $ITERATIONS Java2D default False pyautogui_reader $DATA_DIR
./start_measurement.sh measure $ITERATIONS Java2D rects True pyautogui_reader $DATA_DIR
./start_measurement.sh measure $ITERATIONS Java2D rects False pyautogui_reader $DATA_DIR

./start_measurement.sh measure $ITERATIONS Java2D default True windup_python $DATA_DIR
./start_measurement.sh measure $ITERATIONS Java2D default False windup_python $DATA_DIR
./start_measurement.sh measure $ITERATIONS Java2D rects True windup_python $DATA_DIR
./start_measurement.sh measure $ITERATIONS Java2D rects False windup_python $DATA_DIR

# # # # pyglet ---------------------------------------------------------------------------------------
./start_measurement.sh measure $ITERATIONS pyglet default True ctypes_reader $DATA_DIR
./start_measurement.sh measure $ITERATIONS pyglet default False ctypes_reader $DATA_DIR
./start_measurement.sh measure $ITERATIONS pyglet rects True ctypes_reader $DATA_DIR
./start_measurement.sh measure $ITERATIONS pyglet rects False ctypes_reader $DATA_DIR

./start_measurement.sh measure $ITERATIONS pyglet default True pyautogui_reader $DATA_DIR
./start_measurement.sh measure $ITERATIONS pyglet default False pyautogui_reader $DATA_DIR
./start_measurement.sh measure $ITERATIONS pyglet rects True pyautogui_reader $DATA_DIR
./start_measurement.sh measure $ITERATIONS pyglet rects False pyautogui_reader $DATA_DIR

./start_measurement.sh measure $ITERATIONS pyglet default True windup_python $DATA_DIR
./start_measurement.sh measure $ITERATIONS pyglet default False windup_python $DATA_DIR
./start_measurement.sh measure $ITERATIONS pyglet rects True windup_python $DATA_DIR
./start_measurement.sh measure $ITERATIONS pyglet rects False windup_python $DATA_DIR

# # # # glut ---------------------------------------------------------------------------------------
./start_measurement.sh measure $ITERATIONS GLUT default True ctypes_reader $DATA_DIR
./start_measurement.sh measure $ITERATIONS GLUT default False ctypes_reader $DATA_DIR
./start_measurement.sh measure $ITERATIONS GLUT rects True ctypes_reader $DATA_DIR
./start_measurement.sh measure $ITERATIONS GLUT rects False ctypes_reader $DATA_DIR

./start_measurement.sh measure $ITERATIONS GLUT default True pyautogui_reader $DATA_DIR
./start_measurement.sh measure $ITERATIONS GLUT default False pyautogui_reader $DATA_DIR
./start_measurement.sh measure $ITERATIONS GLUT rects True pyautogui_reader $DATA_DIR
./start_measurement.sh measure $ITERATIONS GLUT rects False pyautogui_reader $DATA_DIR

./start_measurement.sh measure $ITERATIONS GLUT default True windup_python $DATA_DIR
./start_measurement.sh measure $ITERATIONS GLUT default False windup_python $DATA_DIR
./start_measurement.sh measure $ITERATIONS GLUT rects True windup_python $DATA_DIR
./start_measurement.sh measure $ITERATIONS GLUT rects False windup_python $DATA_DIR

# # SDL2 ---------------------------------------------------------------------------------------
./start_measurement.sh measure $ITERATIONS SDL2_Software default True ctypes_reader $DATA_DIR
./start_measurement.sh measure $ITERATIONS SDL2_Software default False ctypes_reader $DATA_DIR
./start_measurement.sh measure $ITERATIONS SDL2_Software rects True ctypes_reader $DATA_DIR
./start_measurement.sh measure $ITERATIONS SDL2_Software rects False ctypes_reader $DATA_DIR
./start_measurement.sh measure $ITERATIONS SDL2_Software default True pyautogui_reader $DATA_DIR
./start_measurement.sh measure $ITERATIONS SDL2_Software default False pyautogui_reader $DATA_DIR
./start_measurement.sh measure $ITERATIONS SDL2_Software rects True pyautogui_reader $DATA_DIR
./start_measurement.sh measure $ITERATIONS SDL2_Software rects False pyautogui_reader $DATA_DIR
./start_measurement.sh measure $ITERATIONS SDL2_Software default True windup_python $DATA_DIR
./start_measurement.sh measure $ITERATIONS SDL2_Software default False windup_python $DATA_DIR
./start_measurement.sh measure $ITERATIONS SDL2_Software rects True windup_python $DATA_DIR
./start_measurement.sh measure $ITERATIONS SDL2_Software rects False windup_python $DATA_DIR

./start_measurement.sh measure $ITERATIONS SDL2_OPENGL default True ctypes_reader $DATA_DIR
./start_measurement.sh measure $ITERATIONS SDL2_OPENGL default False ctypes_reader $DATA_DIR
./start_measurement.sh measure $ITERATIONS SDL2_OPENGL rects True ctypes_reader $DATA_DIR
./start_measurement.sh measure $ITERATIONS SDL2_OPENGL rects False ctypes_reader $DATA_DIR
./start_measurement.sh measure $ITERATIONS SDL2_OPENGL default True pyautogui_reader $DATA_DIR
./start_measurement.sh measure $ITERATIONS SDL2_OPENGL default False pyautogui_reader $DATA_DIR
./start_measurement.sh measure $ITERATIONS SDL2_OPENGL rects True pyautogui_reader $DATA_DIR
./start_measurement.sh measure $ITERATIONS SDL2_OPENGL rects False pyautogui_reader $DATA_DIR
./start_measurement.sh measure $ITERATIONS SDL2_OPENGL default True windup_python $DATA_DIR
./start_measurement.sh measure $ITERATIONS SDL2_OPENGL default False windup_python $DATA_DIR
./start_measurement.sh measure $ITERATIONS SDL2_OPENGL rects True windup_python $DATA_DIR
./start_measurement.sh measure $ITERATIONS SDL2_OPENGL rects False windup_python $DATA_DIR

./start_measurement.sh measure $ITERATIONS SDL2_OpenGLES default True ctypes_reader $DATA_DIR
./start_measurement.sh measure $ITERATIONS SDL2_OpenGLES default False ctypes_reader $DATA_DIR
./start_measurement.sh measure $ITERATIONS SDL2_OpenGLES rects True ctypes_reader $DATA_DIR
./start_measurement.sh measure $ITERATIONS SDL2_OpenGLES rects False ctypes_reader $DATA_DIR
./start_measurement.sh measure $ITERATIONS SDL2_OpenGLES default True pyautogui_reader $DATA_DIR
./start_measurement.sh measure $ITERATIONS SDL2_OpenGLES default False pyautogui_reader $DATA_DIR
./start_measurement.sh measure $ITERATIONS SDL2_OpenGLES rects True pyautogui_reader $DATA_DIR
./start_measurement.sh measure $ITERATIONS SDL2_OpenGLES rects False pyautogui_reader $DATA_DIR
./start_measurement.sh measure $ITERATIONS SDL2_OpenGLES default True windup_python $DATA_DIR
./start_measurement.sh measure $ITERATIONS SDL2_OpenGLES default False windup_python $DATA_DIR
./start_measurement.sh measure $ITERATIONS SDL2_OpenGLES rects True windup_python $DATA_DIR
./start_measurement.sh measure $ITERATIONS SDL2_OpenGLES rects False windup_python $DATA_DIR
