#!/bin/sh

ITERATIONS=100
DATA_DIR="2802_all_and_fullscreens"

READERS=("getpixel" "bitblt" "getdbits" "windup_fullscreen" "none")
#READERS=("getpixel" "bitblt" "getdbits" "pyautogui_reader" "ctypes_reader" "windup_python" "windup")

#FRAMEWORKS=("FLTK" "win32" "pyglet" "tkinter" "pyqt5" "pyqt6" "wxpython" "pygame" "GLUT" "GTK" "Unity" "SDL2_OpenGL" "SDL2_OpenGLES2" "SDL2_OpenGLES" "SDL2_Direct3D" "SDL2_Software" "GLEW_SDL" "Qt5" "Qt6" "DirectX11" "Java2D" "JavaSwing" "Godot" "psychopy_pyglet")
#FRAMEWORKS=("FLTK" "win32" "pyglet" "tkinter" "pyqt5" "pyqt6" "wxpython" "pygame" "GLUT" "GTK" "Unity" "SDL2_OpenGLES" "SDL2_Direct3D" "SDL2_Software" "Qt5" "Qt6" "DirectX11" "JavaSwing" "Java2D" "GLEW_SDL" "SDL2_OpenGL" "SDL2_OpenGLES2" "psychopy_pyglet")
FRAMEWORKS=("Qt5" "Qt6" "DirectX11" "GLEW_SDL" "pygame" "SDL2_OpenGL" "psychopy_pyglet")
#FRAMEWORKS_GLUMPY=("qt5" "sdl" "glfw" "pyglet")


mkdir "./data/$DATA_DIR"
sleep "3s"


for f in "${!FRAMEWORKS[@]}";
do
    for r in "${!READERS[@]}";
    do
        ./start_measurement.sh $ITERATIONS "${FRAMEWORKS[$f]}" default "${READERS[$r]}" fullscreen $DATA_DIR
        ./start_measurement.sh $ITERATIONS "${FRAMEWORKS[$f]}" rects "${READERS[$r]}" fullscreen $DATA_DIR
        ./start_measurement.sh $ITERATIONS "${FRAMEWORKS[$f]}" default "${READERS[$r]}" no_fullscreen $DATA_DIR
        r=$((r+1));
    done
    f=$((f+1));
done


# for glumpy frameworks
# for f in "${!FRAMEWORKS_GLUMPY[@]}";
# do
#     for r in "${!READERS[@]}";
#     do
#         ./start_measurement_glumpy.sh $ITERATIONS "${FRAMEWORKS_GLUMPY[$f]}" default "${READERS[$r]}" fullscreen $DATA_DIR
#         ./start_measurement_glumpy.sh $ITERATIONS "${FRAMEWORKS_GLUMPY[$f]}" rects "${READERS[$r]}" fullscreen $DATA_DIR
#         ./start_measurement_glumpy.sh $ITERATIONS "${FRAMEWORKS_GLUMPY[$f]}" default "${READERS[$r]}" no_fullscreen $DATA_DIR
#         r=$((r+1));
#     done
#     f=$((f+1));
# done


# # java fx no auto start fullscreen
# for r in "${!READERS[@]}";
# do
    # ./start_measurement.sh $ITERATIONS FX default "${READERS[$r]}" fullscreen $DATA_DIR
    # ./start_measurement.sh $ITERATIONS FX rects "${READERS[$r]}" fullscreen $DATA_DIR
#     r=$((r+1));
# done


# # java fx no auto start no-fullscreen
# for r in "${!READERS[@]}";
# do
    # ./start_measurement.sh $ITERATIONS FX default "${READERS[$r]}" no_fullscreen $DATA_DIR
    # ./start_measurement.sh $ITERATIONS FX rects "${READERS[$r]}" no_fullscreen $DATA_DIR
#     r=$((r+1));
# done