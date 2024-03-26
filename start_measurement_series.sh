#!/bin/sh

ITERATIONS=50
DATA_DIR="2503_diverses_mit_images"

READERS=("getpixel" "bitblt" "getdbits" "windup_fullscreen" "none")
#READERS=("getpixel" "bitblt" "getdbits" "pyautogui_reader" "ctypes_reader" "windup_python" "windup")

#FRAMEWORKS=("FLTK" "win32" "pyglet" "tkinter" "pyqt5" "pyqt6" "wxpython" "pygame" "GLUT" "GTK" "SDL2_OpenGL" "SDL2_OpenGLES2" "SDL2_OpenGLES" "SDL2_Direct3D" "SDL2_Software" "GLEW_SDL" "Qt5" "Qt6" "DirectX11" "Java2D" "JavaSwing" "Godot" "Unity" "psychopy_pyglet")
#FRAMEWORKS=("FLTK" "win32" "pyglet" "tkinter" "pyqt5" "pyqt6" "wxpython" "pygame" "GLUT" "GTK" "Unity" "SDL2_OpenGLES" "SDL2_Direct3D" "SDL2_Software" "Qt5" "Qt6" "DirectX11" "JavaSwing" "Java2D" "GLEW_SDL" "SDL2_OpenGL" "SDL2_OpenGLES2" "psychopy_pyglet")
FRAMEWORKS=("Godot" "Unity")
#FRAMEWORKS=("pyglet" "tkinter" "pyqt5" "pyqt6" "wxpython" "pygame" "GLUT" "GTK" "Qt5" "Qt6" "JavaSwing" "Java2D" "psychopy_pyglet")
#FRAMEWORKS_GLUMPY=("qt5" "sdl" "glfw")


mkdir "./data/$DATA_DIR"
sleep "7s"



# for glumpy frameworks
# for f in "${!FRAMEWORKS_GLUMPY[@]}";
# do
#     for r in "${!READERS[@]}";
#     do
#         ./start_measurement_glumpy.sh $ITERATIONS "${FRAMEWORKS_GLUMPY[$f]}" default "${READERS[$r]}" fullscreen $DATA_DIR
#         # ./start_measurement_glumpy.sh $ITERATIONS "${FRAMEWORKS_GLUMPY[$f]}" rects "${READERS[$r]}" fullscreen $DATA_DIR
#         # ./start_measurement_glumpy.sh $ITERATIONS "${FRAMEWORKS_GLUMPY[$f]}" 3D "${READERS[$r]}" fullscreen $DATA_DIR
#         # ./start_measurement_glumpy.sh $ITERATIONS "${FRAMEWORKS_GLUMPY[$f]}" default "${READERS[$r]}" no_fullscreen $DATA_DIR
#         # ./start_measurement_glumpy.sh $ITERATIONS "${FRAMEWORKS_GLUMPY[$f]}" default "${READERS[$r]}" small $DATA_DIR
#         r=$((r+1));
#     done
#     f=$((f+1));
# done


# DATA_DIR="1103_3d_unity"
# mkdir "./data/$DATA_DIR"
# sleep "3s"


for f in "${!FRAMEWORKS[@]}";
do
    for r in "${!READERS[@]}";
    do
        ./start_measurement.sh $ITERATIONS "${FRAMEWORKS[$f]}" default "${READERS[$r]}" fullscreen $DATA_DIR
        ./start_measurement.sh $ITERATIONS "${FRAMEWORKS[$f]}" rects "${READERS[$r]}" fullscreen $DATA_DIR
        ./start_measurement.sh $ITERATIONS "${FRAMEWORKS[$f]}" image "${READERS[$r]}" fullscreen $DATA_DIR
        #./start_measurement.sh $ITERATIONS "${FRAMEWORKS[$f]}" 3D "${READERS[$r]}" fullscreen $DATA_DIR
        #./start_measurement.sh $ITERATIONS "${FRAMEWORKS[$f]}" default "${READERS[$r]}" no_fullscreen $DATA_DIR
        #./start_measurement.sh $ITERATIONS "${FRAMEWORKS[$f]}" default "${READERS[$r]}" small $DATA_DIR
        r=$((r+1));
    done
    f=$((f+1));
done

# for r in "${!READERS[@]}";
# do
#     ./start_measurement.sh $ITERATIONS Direct3D default "${READERS[$r]}" no_fullscreen $DATA_DIR
#     ./start_measurement.sh $ITERATIONS Direct3D default "${READERS[$r]}" small $DATA_DIR
#     r=$((r+1));
# done

for r in "${!READERS[@]}";
do
    ./start_measurement.sh $ITERATIONS Unity 3D "${READERS[$r]}" fullscreen $DATA_DIR
    ./start_measurement.sh $ITERATIONS Unity default "${READERS[$r]}" no_fullscreen $DATA_DIR
    #./start_measurement.sh $ITERATIONS Unity default "${READERS[$r]}" small $DATA_DIR
    r=$((r+1));
done

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