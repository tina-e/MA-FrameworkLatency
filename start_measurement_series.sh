#!/bin/sh

ITERATIONS=10
#DATA_DIR="2002_gdi_readers_newsetup"
DATA_DIR="debug"
#DATA_DIR="1902_test"
#DATA_DIR="2002_newsetup_printf"

#READERS=("windup" "getpixel" "bitblt" "getdbits")
#READERS=("getpixel" "bitblt" "getdbits" "pyautogui_reader" "ctypes_reader" "windup_python" "windup")
#READERS=("windup_stem")
READERS=("windup_schmatzer2")

#FRAMEWORKS=("FLTK" "win32" "pyglet" "tkinter" "pyqt5" "pyqt6" "wxpython" "pygame" "GLUT" "GTK" "Unity" "SDL2_OpenGL" "SDL2_OpenGLES2" "SDL2_OpenGLES" "SDL2_Direct3D" "SDL2_Software" "GLEW_SDL" "Qt5" "Qt6" "DirectX11" "Java2D" "JavaSwing" "Godot" "psychopy_pyglet" "psychopy_pygame" "psychopy_glfw")
#FRAMEWORKS=("FLTK" "win32" "pyglet" "tkinter" "pyqt5" "pyqt6" "wxpython" "pygame" "GLUT" "GTK" "Unity" "SDL2_OpenGLES" "SDL2_Direct3D" "SDL2_Software" "Qt5" "Qt6" "DirectX11" "JavaSwing" "Java2D" "GLEW_SDL" "SDL2_OpenGL" "SDL2_OpenGLES2" "psychopy_pyglet" "psychopy_pygame" "psychopy_glfw")
FRAMEWORKS=("GLEW_SDL")

# to debug
#FRAMEWORKS=("SDL2_OpenGL" "SDL2_OpenGLES2")

#FRAMEWORKS=("SDL2_OpenGLES2")


#FRAMEWORKS_GLUMPY=("pyglet" "glfw" "qt5" "sdl")


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


# measure end to end only
# for f in "${!FRAMEWORKS[@]}";
# do
#     if [ "$f" -eq 0 ]
#     then
#         ./start_measurement.sh $ITERATIONS "${FRAMEWORKS[$f]}" default False getpixel $DATA_DIR
#         ./start_measurement.sh $ITERATIONS "${FRAMEWORKS[$f]}" rects False getpixel $DATA_DIR
#     else
#         ./start_measurement.sh $ITERATIONS "${FRAMEWORKS[$f]}" default False getpixel $DATA_DIR
#         ./start_measurement.sh $ITERATIONS "${FRAMEWORKS[$f]}" rects False getpixel $DATA_DIR
#     fi
#     f=$((f+1));
# done


# for f in "${!FRAMEWORKS[@]}";
# do
#     for r in "${!READERS[@]}";
#     do
#         ./start_measurement.sh $ITERATIONS "${FRAMEWORKS[$f]}" default True "${READERS[$r]}" $DATA_DIR
#         ./start_measurement.sh $ITERATIONS "${FRAMEWORKS[$f]}" default False "${READERS[$r]}" $DATA_DIR
#         ./start_measurement.sh $ITERATIONS "${FRAMEWORKS[$f]}" rects True "${READERS[$r]}" $DATA_DIR
#         ./start_measurement.sh $ITERATIONS "${FRAMEWORKS[$f]}" rects False "${READERS[$r]}" $DATA_DIR
#         r=$((r+1));
#     done
#     f=$((f+1));
# done


# measure SDLs
# for f in "${!FRAMEWORKS_SDL[@]}";
# do
#     for r in "${!READERS[@]}";
#     do
#         if [ "$f" -eq 0 ] && [ "$r" -eq 0 ]
#         then
#             ./start_measurement_SDL.sh $ITERATIONS "${FRAMEWORKS_SDL[$f]}" default True "${READERS[$r]}" $DATA_DIR
#             ./start_measurement_SDL.sh $ITERATIONS "${FRAMEWORKS_SDL[$f]}" default False "${READERS[$r]}" $DATA_DIR
#             ./start_measurement_SDL.sh $ITERATIONS "${FRAMEWORKS_SDL[$f]}" rects True "${READERS[$r]}" $DATA_DIR
#             ./start_measurement_SDL.sh $ITERATIONS "${FRAMEWORKS_SDL[$f]}" rects False "${READERS[$r]}" $DATA_DIR
#         else
#             ./start_measurement_SDL.sh $ITERATIONS "${FRAMEWORKS_SDL[$f]}" default True "${READERS[$r]}" $DATA_DIR
#             ./start_measurement_SDL.sh $ITERATIONS "${FRAMEWORKS_SDL[$f]}" default False "${READERS[$r]}" $DATA_DIR
#             ./start_measurement_SDL.sh $ITERATIONS "${FRAMEWORKS_SDL[$f]}" rects True "${READERS[$r]}" $DATA_DIR
#             ./start_measurement_SDL.sh $ITERATIONS "${FRAMEWORKS_SDL[$f]}" rects False "${READERS[$r]}" $DATA_DIR
#         fi
#         r=$((r+1));
#     done
#     f=$((f+1));
# done


# # for glumpy frameworks
# for f in "${!FRAMEWORKS_GLUMPY[@]}";
# do
#     for r in "${!READERS[@]}";
#     do
#         if [ "$f" -eq 0 ] && [ "$r" -eq 0 ]
#         then
#             ./start_measurement_glumpy.sh $ITERATIONS "${FRAMEWORKS_GLUMPY[$f]}" default True "${READERS[$r]}" $DATA_DIR
#             ./start_measurement_glumpy.sh $ITERATIONS "${FRAMEWORKS_GLUMPY[$f]}" default False "${READERS[$r]}" $DATA_DIR
#             ./start_measurement_glumpy.sh $ITERATIONS "${FRAMEWORKS_GLUMPY[$f]}" rects True "${READERS[$r]}" $DATA_DIR
#             ./start_measurement_glumpy.sh $ITERATIONS "${FRAMEWORKS_GLUMPY[$f]}" rects False "${READERS[$r]}" $DATA_DIR
#         else
#             ./start_measurement_glumpy.sh $ITERATIONS "${FRAMEWORKS_GLUMPY[$f]}" default True "${READERS[$r]}" $DATA_DIR
#             ./start_measurement_glumpy.sh $ITERATIONS "${FRAMEWORKS_GLUMPY[$f]}" default False "${READERS[$r]}" $DATA_DIR
#             ./start_measurement_glumpy.sh $ITERATIONS "${FRAMEWORKS_GLUMPY[$f]}" rects True "${READERS[$r]}" $DATA_DIR
#             ./start_measurement_glumpy.sh $ITERATIONS "${FRAMEWORKS_GLUMPY[$f]}" rects False "${READERS[$r]}" $DATA_DIR
#         fi
#         r=$((r+1));
#     done
#     f=$((f+1));
# done

# java fx no auto start possible for now
# for r in "${!READERS[@]}";
# do
#     if [ "$r" -eq 0 ]
#     then
#         ./start_measurement.sh $ITERATIONS FX default True "${READERS[$r]}" $DATA_DIR
#         ./start_measurement.sh $ITERATIONS FX default False "${READERS[$r]}" $DATA_DIR
#         ./start_measurement.sh $ITERATIONS FX rects True "${READERS[$r]}" $DATA_DIR
#         ./start_measurement.sh $ITERATIONS FX rects False "${READERS[$r]}" $DATA_DIR
#     else
#         ./start_measurement.sh $ITERATIONS FX default True "${READERS[$r]}" $DATA_DIR
#         ./start_measurement.sh $ITERATIONS FX default False "${READERS[$r]}" $DATA_DIR
#         ./start_measurement.sh $ITERATIONS FX rects True "${READERS[$r]}" $DATA_DIR
#         ./start_measurement.sh $ITERATIONS FX rects False "${READERS[$r]}" $DATA_DIR
#     fi
#     r=$((r+1));
# done


# glew sdl no auto start possible for now
# for r in "${!READERS[@]}";
# do
#     #./start_measurement.sh $ITERATIONS GLEW_SDL default True "${READERS[$r]}" $DATA_DIR
#     #./start_measurement.sh $ITERATIONS GLEW_SDL default False "${READERS[$r]}" $DATA_DIR
#     ./start_measurement.sh $ITERATIONS GLEW_SDL rects True "${READERS[$r]}" $DATA_DIR
#     ./start_measurement.sh $ITERATIONS GLEW_SDL rects False "${READERS[$r]}" $DATA_DIR
#     r=$((r+1));
# done

# sdl opengles2 rects windup - no auto start 
for r in "${!READERS[@]}";
do
    #./start_measurement.sh $ITERATIONS GLEW_SDL default True "${READERS[$r]}" $DATA_DIR
    #./start_measurement.sh $ITERATIONS GLEW_SDL default False "${READERS[$r]}" $DATA_DIR
    ./start_measurement.sh $ITERATIONS SDL2_OpenGL rects True "${READERS[$r]}" $DATA_DIR
    #./start_measurement.sh $ITERATIONS SDL2_OpenGL rects False "${READERS[$r]}" $DATA_DIR
    r=$((r+1));
done