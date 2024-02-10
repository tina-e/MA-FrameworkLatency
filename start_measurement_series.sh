#!/bin/sh

ITERATIONS=2
DATA_DIR="SDL_vsync_1002_test"

#READERS=("getpixel" "bitblt" "getdbits")
#READERS=("getpixel" "bitblt" "getdbits" "pyautogui_reader" "ctypes_reader" "windup_python" "windup")

#READERS=("windup" "getpixel" "bitblt" "getdbits")
READERS=("windup" "getpixel")

# FRAMEWORKS=("GTK" "FLTK" "win32" "pyglet" "Java2D" "JavaSwing" "tkinter" "pyqt5" "pyqt6" "wxpython" "pygame" "SDL2_OpenGLES" "SDL2_OpenGLES2" "SDL2_OpenGL" "SDL2_Software" "SDL2_Direct3D" "GLEW" "GLUT")
# FRAMEWORKS_SEP_FOLDERS=("Qt5" "Qt6" "DirectX11")

# FRAMEWORKS=("Java2D" "JavaSwing")
# FRAMEWORKS_SEP_FOLDERS=("DirectX11")

#FRAMEWORKS=("SDL2_OpenGLES" "SDL2_OpenGLES2" "SDL2_OpenGL" "SDL2_Software" "SDL2_Direct3D" "SDL2_OpenGLES_vsync" "SDL2_OpenGLES2_vsync" "SDL2_OpenGL_vsync" "SDL2_Software_vsync" "SDL2_Direct3D_vsync" "GLEW_SDL" "GLEW_SDL_vsync")
FRAMEWORKS=("SDL2_OpenGLES" "SDL2_Direct3D_vsync" "GLEW_SDL" "GLEW_SDL_vsync")

#FRAMEWORKS_GLUMPY=("pyglet" "glfw" "qt5" "sdl")
#FRAMEWORKS=("win32")

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

# ./start_measurement.sh calibrate_and_measure $ITERATIONS FLTK default True windup $DATA_DIR
# # ./start_measurement.sh measure $ITERATIONS FLTK default False windup $DATA_DIR
# ./start_measurement.sh measure $ITERATIONS GLEW default True windup $DATA_DIR
# ./start_measurement.sh measure $ITERATIONS GLEW default False windup $DATA_DIR


# ./start_measurement.sh calibrate_and_measure $ITERATIONS GTK rects True pixelreader $DATA_DIR
# ./start_measurement.sh measure $ITERATIONS GTK rects False pixelreader $DATA_DIR
# ./start_measurement.sh calibrate_and_measure $ITERATIONS GTK default True pixelreader_bitblt $DATA_DIR
# ./start_measurement.sh measure $ITERATIONS GTK default False pixelreader_bitblt $DATA_DIR
# ./start_measurement.sh measure $ITERATIONS GTK default True pixelreader_getdbits $DATA_DIR
# ./start_measurement.sh measure $ITERATIONS GTK default False pixelreader_getdbits $DATA_DIR

# measure end to end only
# for f in "${!FRAMEWORKS[@]}";
# do
#     if [ "$f" -eq 0 ]
#     then
#         ./start_measurement.sh calibrate_and_measure $ITERATIONS "${FRAMEWORKS[$f]}" default False getpixel $DATA_DIR
#         ./start_measurement.sh measure $ITERATIONS "${FRAMEWORKS[$f]}" rects False getpixel $DATA_DIR
#     else
#         ./start_measurement.sh measure $ITERATIONS "${FRAMEWORKS[$f]}" default False getpixel $DATA_DIR
#         ./start_measurement.sh measure $ITERATIONS "${FRAMEWORKS[$f]}" rects False getpixel $DATA_DIR
#     fi
#     f=$((f+1));
# done

# measure SDLs
for f in "${!FRAMEWORKS[@]}";
do
    for r in "${!READERS[@]}";
    do
        if [ "$f" -eq 0 ] && [ "$r" -eq 0 ]
        then
            ./start_measurement_SDL.sh calibrate_and_measure $ITERATIONS "${FRAMEWORKS[$f]}" default True "${READERS[$r]}" $DATA_DIR
            ./start_measurement_SDL.sh measure $ITERATIONS "${FRAMEWORKS[$f]}" default False "${READERS[$r]}" $DATA_DIR
            ./start_measurement_SDL.sh measure $ITERATIONS "${FRAMEWORKS[$f]}" rects True "${READERS[$r]}" $DATA_DIR
            ./start_measurement_SDL.sh measure $ITERATIONS "${FRAMEWORKS[$f]}" rects False "${READERS[$r]}" $DATA_DIR
        else
            ./start_measurement_SDL.sh measure $ITERATIONS "${FRAMEWORKS[$f]}" default True "${READERS[$r]}" $DATA_DIR
            ./start_measurement_SDL.sh measure $ITERATIONS "${FRAMEWORKS[$f]}" default False "${READERS[$r]}" $DATA_DIR
            ./start_measurement_SDL.sh measure $ITERATIONS "${FRAMEWORKS[$f]}" rects True "${READERS[$r]}" $DATA_DIR
            ./start_measurement_SDL.sh measure $ITERATIONS "${FRAMEWORKS[$f]}" rects False "${READERS[$r]}" $DATA_DIR
        fi
        r=$((r+1));
    done
    f=$((f+1));
done


# for f in "${!FRAMEWORKS[@]}";
# do
#     for r in "${!READERS[@]}";
#     do
#         if [ "$f" -eq 0 ] && [ "$r" -eq 0 ]
#         then
#             ./start_measurement.sh calibrate_and_measure $ITERATIONS "${FRAMEWORKS[$f]}" default True "${READERS[$r]}" $DATA_DIR
#             ./start_measurement.sh measure $ITERATIONS "${FRAMEWORKS[$f]}" default False "${READERS[$r]}" $DATA_DIR
#             ./start_measurement.sh measure $ITERATIONS "${FRAMEWORKS[$f]}" rects True "${READERS[$r]}" $DATA_DIR
#             ./start_measurement.sh measure $ITERATIONS "${FRAMEWORKS[$f]}" rects False "${READERS[$r]}" $DATA_DIR
#         else
#             ./start_measurement.sh measure $ITERATIONS "${FRAMEWORKS[$f]}" default True "${READERS[$r]}" $DATA_DIR
#             ./start_measurement.sh measure $ITERATIONS "${FRAMEWORKS[$f]}" default False "${READERS[$r]}" $DATA_DIR
#             ./start_measurement.sh measure $ITERATIONS "${FRAMEWORKS[$f]}" rects True "${READERS[$r]}" $DATA_DIR
#             ./start_measurement.sh measure $ITERATIONS "${FRAMEWORKS[$f]}" rects False "${READERS[$r]}" $DATA_DIR
#         fi
#         r=$((r+1));
#     done
#     f=$((f+1));
# done


# # for frameworks where default and rects are not in the same directory
# for f in "${!FRAMEWORKS_SEP_FOLDERS[@]}";
# do
#     for r in "${!READERS[@]}";
#     do
#         if [ "$f" -eq 0 ] && [ "$r" -eq 0 ]
#         then
#             ./start_measurement_sep.sh calibrate_and_measure $ITERATIONS "${FRAMEWORKS_SEP_FOLDERS[$f]}" default True "${READERS[$r]}" $DATA_DIR
#             ./start_measurement_sep.sh measure $ITERATIONS "${FRAMEWORKS_SEP_FOLDERS[$f]}" default False "${READERS[$r]}" $DATA_DIR
#             # ./start_measurement_sep.sh measure $ITERATIONS "${FRAMEWORKS_SEP_FOLDERS[$f]}" rects True "${READERS[$r]}" $DATA_DIR
#             # ./start_measurement_sep.sh measure $ITERATIONS "${FRAMEWORKS_SEP_FOLDERS[$f]}" rects False "${READERS[$r]}" $DATA_DIR
#         else
#             ./start_measurement_sep.sh measure $ITERATIONS "${FRAMEWORKS_SEP_FOLDERS[$f]}" default True "${READERS[$r]}" $DATA_DIR
#             ./start_measurement_sep.sh measure $ITERATIONS "${FRAMEWORKS_SEP_FOLDERS[$f]}" default False "${READERS[$r]}" $DATA_DIR
#             # ./start_measurement_sep.sh measure $ITERATIONS "${FRAMEWORKS_SEP_FOLDERS[$f]}" rects True "${READERS[$r]}" $DATA_DIR
#             # ./start_measurement_sep.sh measure $ITERATIONS "${FRAMEWORKS_SEP_FOLDERS[$f]}" rects False "${READERS[$r]}" $DATA_DIR
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
#             ./start_measurement_glumpy.sh calibrate_and_measure $ITERATIONS "${FRAMEWORKS_GLUMPY[$f]}" default True "${READERS[$r]}" $DATA_DIR
#             ./start_measurement_glumpy.sh measure $ITERATIONS "${FRAMEWORKS_GLUMPY[$f]}" default False "${READERS[$r]}" $DATA_DIR
#             ./start_measurement_glumpy.sh measure $ITERATIONS "${FRAMEWORKS_GLUMPY[$f]}" rects True "${READERS[$r]}" $DATA_DIR
#             ./start_measurement_glumpy.sh measure $ITERATIONS "${FRAMEWORKS_GLUMPY[$f]}" rects False "${READERS[$r]}" $DATA_DIR
#         else
#             ./start_measurement_glumpy.sh measure $ITERATIONS "${FRAMEWORKS_GLUMPY[$f]}" default True "${READERS[$r]}" $DATA_DIR
#             ./start_measurement_glumpy.sh measure $ITERATIONS "${FRAMEWORKS_GLUMPY[$f]}" default False "${READERS[$r]}" $DATA_DIR
#             ./start_measurement_glumpy.sh measure $ITERATIONS "${FRAMEWORKS_GLUMPY[$f]}" rects True "${READERS[$r]}" $DATA_DIR
#             ./start_measurement_glumpy.sh measure $ITERATIONS "${FRAMEWORKS_GLUMPY[$f]}" rects False "${READERS[$r]}" $DATA_DIR
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
#         ./start_measurement.sh calibrate_and_measure $ITERATIONS FX default True "${READERS[$r]}" $DATA_DIR
#         ./start_measurement.sh measure $ITERATIONS FX default False "${READERS[$r]}" $DATA_DIR
#         ./start_measurement.sh calibrate_and_measure $ITERATIONS FX rects True "${READERS[$r]}" $DATA_DIR
#         ./start_measurement.sh measure $ITERATIONS FX rects False "${READERS[$r]}" $DATA_DIR
#     else
#         ./start_measurement.sh measure $ITERATIONS FX default True "${READERS[$r]}" $DATA_DIR
#         ./start_measurement.sh measure $ITERATIONS FX default False "${READERS[$r]}" $DATA_DIR
#         ./start_measurement.sh measure $ITERATIONS FX rects True "${READERS[$r]}" $DATA_DIR
#         ./start_measurement.sh measure $ITERATIONS FX rects False "${READERS[$r]}" $DATA_DIR
#     fi
#     r=$((r+1));
# done