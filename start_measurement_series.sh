#!/bin/sh

ITERATIONS=50
DATA_DIR="windup"

READERS=("getpixel" "bitblt" "getdbits")
#READERS=("getpixel" "bitblt" "getdbits" "pyautogui_reader" "ctypes_reader" "windup_python" "windup")

FRAMEWORKS=("GLEW" "win32" "FLTK" "GLUT" "pyglet" "Java2D" "JavaSwing" "tkinter" "pyqt5" "pyqt6" "wxpython" "pygame" "SDL2_OpenGLES" "SDL2_OPENGL" "SDL2_Software")
FRAMEWORKS_SEP_FOLDERS=("Qt5" "Qt6" "DirectX11")

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

for f in "${!FRAMEWORKS[@]}";
do
    for r in "${!READERS[@]}";
    do
        if [ "$f" -eq 0 ] && [ "$r" -eq 0 ]
        then
            ./start_measurement.sh calibrate_and_measure $ITERATIONS "${FRAMEWORKS[$f]}" default True "${READERS[$r]}" $DATA_DIR
            ./start_measurement.sh measure $ITERATIONS "${FRAMEWORKS[$f]}" default False "${READERS[$r]}" $DATA_DIR
            ./start_measurement.sh measure $ITERATIONS "${FRAMEWORKS[$f]}" rects True "${READERS[$r]}" $DATA_DIR
            ./start_measurement.sh measure $ITERATIONS "${FRAMEWORKS[$f]}" rects False "${READERS[$r]}" $DATA_DIR
        else
            ./start_measurement.sh measure $ITERATIONS "${FRAMEWORKS[$f]}" default True "${READERS[$r]}" $DATA_DIR
            ./start_measurement.sh measure $ITERATIONS "${FRAMEWORKS[$f]}" default False "${READERS[$r]}" $DATA_DIR
            ./start_measurement.sh measure $ITERATIONS "${FRAMEWORKS[$f]}" rects True "${READERS[$r]}" $DATA_DIR
            ./start_measurement.sh measure $ITERATIONS "${FRAMEWORKS[$f]}" rects False "${READERS[$r]}" $DATA_DIR
        fi
        r=$((r+1));
    done
    f=$((f+1));
done


# for frameworks where default and rects are not in the same directory
for f in "${!FRAMEWORKS_SEP_FOLDERS[@]}";
do
    for r in "${!READERS[@]}";
    do
        if [ "$f" -eq 0 ] && [ "$r" -eq 0 ]
        then
            ./start_measurements_sep.sh calibrate_and_measure $ITERATIONS "${FRAMEWORKS_SEP_FOLDERS[$f]}" default True "${READERS[$r]}" $DATA_DIR
            ./start_measurements_sep.sh measure $ITERATIONS "${FRAMEWORKS_SEP_FOLDERS[$f]}" default False "${READERS[$r]}" $DATA_DIR
            ./start_measurements_sep.sh measure $ITERATIONS "${FRAMEWORKS_SEP_FOLDERS[$f]}" rects True "${READERS[$r]}" $DATA_DIR
            ./start_measurements_sep.sh measure $ITERATIONS "${FRAMEWORKS_SEP_FOLDERS[$f]}" rects False "${READERS[$r]}" $DATA_DIR
        else
            ./start_measurements_sep.sh measure $ITERATIONS "${FRAMEWORKS_SEP_FOLDERS[$f]}" default True "${READERS[$r]}" $DATA_DIR
            ./start_measurements_sep.sh measure $ITERATIONS "${FRAMEWORKS_SEP_FOLDERS[$f]}" default False "${READERS[$r]}" $DATA_DIR
            ./start_measurements_sep.sh measure $ITERATIONS "${FRAMEWORKS_SEP_FOLDERS[$f]}" rects True "${READERS[$r]}" $DATA_DIR
            ./start_measurements_sep.sh measure $ITERATIONS "${FRAMEWORKS_SEP_FOLDERS[$f]}" rects False "${READERS[$r]}" $DATA_DIR
        fi
        r=$((r+1));
    done
    f=$((f+1));
done