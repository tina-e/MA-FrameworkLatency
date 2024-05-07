#!/bin/sh

ITERATIONS=50
DATA_DIR="vsync_tester_0605_60hz"

#READERS=("windup_fullscreen" "getpixel" "bitblt" "getdbits" "none")
READERS=("windup_fullscreen" "getpixel")
#READERS=("getpixel" "bitblt" "getdbits" "pyautogui_reader" "ctypes_reader" "windup_python" "windup")
#FRAMEWORKS=("FLTK" "win32" "pyglet" "tkinter" "pyqt5" "pyqt6" "wxpython" "pygame" "GLUT" "GTK" "SDL2_OpenGL" "SDL2_OpenGLES2" "SDL2_OpenGLES" "SDL2_Direct3D" "SDL2_Software" "GLEW_SDL" "Qt5" "Qt6" "DirectX11" "Java2D" "JavaSwing" "Godot" "Unity" "psychopy_pyglet")

FRAMEWORKS_3D=("Direct3D" "GLEW_SDL" "GLUT" "pygame" "pyglet" "Unity")
FRAMEWORKS_IMAGE=("GLUT" "Godot" "GTK" "Java2D" "JavaSwing" "pygame" "pyglet" "pyqt5" "pyqt6" "Qt5" "Qt6" "tkinter" "Unity" "wxpython")
FRAMEWORKS_FULLSCREEN_AND_RECTS=("Direct3D" "FLTK" "GLEW_SDL" "GLUT" "Godot" "GTK" "Java2D" "JavaSwing" "pygame" "pyglet" "pyqt5" "pyqt6" "Qt5" "Qt6" "SDL2_OpenGL" "SDL2_OpenGLES2" "SDL2_OpenGLES" "SDL2_Direct3D" "SDL2_Software" "tkinter" "Unity" "win32" "wxpython" "psychopy_pyglet")
FRAMEWORKS_NO_FULLSCREEN=("Direct3D" "FLTK" "GLEW_SDL" "GLUT" "GTK" "Java2D" "JavaSwing" "pygame" "pyglet" "pyqt5" "pyqt6" "Qt5" "Qt6" "SDL2_OpenGL" "SDL2_OpenGLES2" "SDL2_OpenGLES" "SDL2_Direct3D" "SDL2_Software" "tkinter" "Unity" "win32" "wxpython")


# measurements 2704 recompileds
FRAMEWORKS_BIG=("GLEW_SDL" "GLUT" "GTK" "Java2D" "JavaSwing" "pygame" "pyglet" "pyqt5" "pyqt6" "Qt5" "Qt6" "SDL2_OpenGL" "SDL2_OpenGLES2" "SDL2_OpenGLES" "SDL2_Direct3D" "SDL2_Software" "tkinter" "win32" "wxpython")
FRAMEWORKS_FS=("Direct3D" "FLTK" "GLEW_SDL" "GLUT" "GTK" "Java2D" "JavaSwing" "pygame" "pyglet" "pyqt5" "pyqt6" "Qt5" "Qt6" "SDL2_OpenGL" "SDL2_OpenGLES2" "SDL2_OpenGLES" "SDL2_Direct3D" "SDL2_Software" "tkinter" "win32" "wxpython")
# end measurements 2704 recompileds


#FRAMEWORKS_SMALL=("Direct3D" "FLTK" "GLEW_SDL" "GLUT" "GTK" "Java2D" "JavaSwing" "pygame" "pyglet" "pyqt5" "pyqt6" "Qt5" "Qt6" "SDL2_OpenGL" "SDL2_OpenGLES2" "SDL2_OpenGLES" "SDL2_Direct3D" "SDL2_Software" "tkinter" "win32" "wxpython")
FRAMEWORKS_SMALL=("Qt5" "Qt6" "SDL2_OpenGL" "SDL2_OpenGLES2" "SDL2_OpenGLES" "SDL2_Direct3D" "SDL2_Software" "tkinter" "win32" "wxpython")

FRAMEWORK_GLUMPY=("qt5" "sdl" "glfw")

FRAMEWORK_SDLS=("SDL2_OpenGL" "SDL2_OpenGLES2" "SDL2_OpenGLES" "SDL2_Direct3D" "SDL2_Software")

FRAMEWORKS=("Direct3D" "FLTK" "GLEW_SDL" "GLUT" "GTK" "Java2D" "JavaSwing" "pygame" "pyglet" "pyqt5" "pyqt6" "Qt5" "Qt6" "SDL2_OpenGL" "SDL2_OpenGLES2" "SDL2_OpenGLES" "SDL2_Direct3D" "SDL2_Software" "tkinter" "win32" "wxpython")

mkdir "./data/$DATA_DIR"
sleep "7s"


# measurements 2704 recompileds
for f in "${!FRAMEWORKS[@]}";
do
    for r in "${!READERS[@]}";
    do
        #./start_measurement.sh $ITERATIONS "${FRAMEWORKS_BIG[$f]}" default "${READERS[$r]}" big $DATA_DIR
        #./start_measurement.sh $ITERATIONS "${FRAMEWORKS_BIG[$f]}" default "${READERS[$r]}" small $DATA_DIR
        #./start_measurement.sh $ITERATIONS "${FRAMEWORKS_BIG[$f]}" default "${READERS[$r]}" no_fullscreen $DATA_DIR
        ./start_measurement.sh $ITERATIONS "${FRAMEWORKS[$f]}" default "${READERS[$r]}" fullscreen $DATA_DIR
        r=$((r+1));
    done
    f=$((f+1));
done
# end measurements 2704 recompileds


# for f in "${!FRAMEWORK_SDLS[@]}";
# do
#     for r in "${!READERS[@]}";
#     do
#         ./start_measurement.sh $ITERATIONS "${FRAMEWORK_SDLS[$f]}" image "${READERS[$r]}" fullscreen $DATA_DIR
#         ./start_measurement.sh $ITERATIONS "${FRAMEWORK_SDLS[$f]}" default "${READERS[$r]}" fullscreen $DATA_DIR
#         ./start_measurement.sh $ITERATIONS "${FRAMEWORK_SDLS[$f]}" rects "${READERS[$r]}" fullscreen $DATA_DIR
#         r=$((r+1));
#     done
#     f=$((f+1));
# done

# for r in "${!READERS[@]}";
# do
#     ./start_measurement.sh $ITERATIONS psychopy_pyglet default "${READERS[$r]}" no_fullscreen $DATA_DIR
#     ./start_measurement.sh $ITERATIONS psychopy_pyglet default "${READERS[$r]}" small $DATA_DIR
#     r=$((r+1));
# done

# for r in "${!READERS[@]}";
# do
#     ./start_measurement.sh $ITERATIONS Godot 3D "${READERS[$r]}" fullscreen $DATA_DIR
#     ./start_measurement.sh $ITERATIONS Godot default "${READERS[$r]}" no_fullscreen $DATA_DIR
#     ./start_measurement.sh $ITERATIONS Godot default "${READERS[$r]}" small $DATA_DIR
#     r=$((r+1));
# done

# default and rects
# for f in "${!FRAMEWORKS_FULLSCREEN_AND_RECTS[@]}";
# do
#     for r in "${!READERS[@]}";
#     do
#         ./start_measurement.sh $ITERATIONS "${FRAMEWORKS_FULLSCREEN_AND_RECTS[$f]}" default "${READERS[$r]}" fullscreen $DATA_DIR
#         ./start_measurement.sh $ITERATIONS "${FRAMEWORKS_FULLSCREEN_AND_RECTS[$f]}" rects "${READERS[$r]}" fullscreen $DATA_DIR
#         r=$((r+1));
#     done
#     f=$((f+1));
# done


# ./start_measurement.sh $ITERATIONS pyqt6 default windup_fullscreen small $DATA_DIR
# ./start_measurement.sh $ITERATIONS Direct3D default getdbits fullscreen $DATA_DIR
# ./start_measurement.sh $ITERATIONS Direct3D default getpixel fullscreen $DATA_DIR
# ./start_measurement.sh $ITERATIONS pyglet default getdbits fullscreen $DATA_DIR
# ./start_measurement.sh $ITERATIONS pyglet default bitblt fullscreen $DATA_DIR

# todo seltsam
# ./start_measurement.sh $ITERATIONS pyglet 3D getpixel fullscreen $DATA_DIR
# ./start_measurement.sh $ITERATIONS pyglet 3D bitblt fullscreen $DATA_DIR
# ./start_measurement.sh $ITERATIONS pyglet 3D getdbits fullscreen $DATA_DIR

# ./start_measurement.sh $ITERATIONS GLUT 3D windup_fullscreen fullscreen $DATA_DIR

# sleep "3s"

# for r in "${!READERS[@]}";
# do
#     ./start_measurement.sh $ITERATIONS Godot default "${READERS[$r]}" fullscreen $DATA_DIR
#     ./start_measurement.sh $ITERATIONS Godot image "${READERS[$r]}" fullscreen $DATA_DIR
#     ./start_measurement.sh $ITERATIONS Godot rects "${READERS[$r]}" fullscreen $DATA_DIR
#     r=$((r+1));
# done

# sleep "3s"

# for r in "${!READERS[@]}";
# do
#     ./start_measurement.sh $ITERATIONS GLEW_SDL default "${READERS[$r]}" fullscreen $DATA_DIR
#     ./start_measurement.sh $ITERATIONS GLEW_SDL rects "${READERS[$r]}" fullscreen $DATA_DIR
#     ./start_measurement.sh $ITERATIONS GLEW_SDL image "${READERS[$r]}" fullscreen $DATA_DIR
#     ./start_measurement.sh $ITERATIONS GLEW_SDL 3D "${READERS[$r]}" fullscreen $DATA_DIR
#     ./start_measurement.sh $ITERATIONS GLEW_SDL default "${READERS[$r]}" no_fullscreen $DATA_DIR
#     ./start_measurement.sh $ITERATIONS GLEW_SDL default "${READERS[$r]}" small $DATA_DIR
#     r=$((r+1));
# done

# sleep "3s"

# ./start_measurement.sh $ITERATIONS Godot 3D none fullscreen $DATA_DIR
# ./start_measurement.sh $ITERATIONS psychopy_pyglet rects none fullscreen $DATA_DIR
# ./start_measurement.sh $ITERATIONS psychopy_pyglet image none fullscreen $DATA_DIR


# # condition image
# for f in "${!FRAMEWORKS_IMAGE[@]}";
# do
#     for r in "${!READERS[@]}";
#     do
#         ./start_measurement.sh $ITERATIONS "${FRAMEWORKS_IMAGE[$f]}" image "${READERS[$r]}" fullscreen $DATA_DIR
#         r=$((r+1));
#     done
#     f=$((f+1));
# done

# sleep "3s"

# # no fullscreen
# for f in "${!FRAMEWORKS_NO_FULLSCREEN[@]}";
# do
#     for r in "${!READERS[@]}";
#     do
#         ./start_measurement.sh $ITERATIONS "${FRAMEWORKS_NO_FULLSCREEN[$f]}" default "${READERS[$r]}" no_fullscreen $DATA_DIR
#         r=$((r+1));
#     done
#     f=$((f+1));
# done

# sleep "3s"

# condition 3D
# for f in "${!FRAMEWORKS_3D[@]}";
# do
#     for r in "${!READERS[@]}";
#     do
#         ./start_measurement.sh $ITERATIONS "${FRAMEWORKS_3D[$f]}" 3D "${READERS[$r]}" fullscreen $DATA_DIR
#         r=$((r+1));
#     done
#     f=$((f+1));
# done

# sleep "3s"

# small
# for f in "${!FRAMEWORKS_SMALL[@]}";
# do
#     for r in "${!READERS[@]}";
#     do
#         ./start_measurement.sh $ITERATIONS "${FRAMEWORKS_SMALL[$f]}" default "${READERS[$r]}" small $DATA_DIR
#         r=$((r+1));
#     done
#     f=$((f+1));
# done

# sleep "3s"

# for glumpy frameworks
# for f in "${!FRAMEWORKS_GLUMPY[@]}";
# do
#     for r in "${!READERS[@]}";
#     do
#         ./start_measurement_glumpy.sh $ITERATIONS "${FRAMEWORKS_GLUMPY[$f]}" default "${READERS[$r]}" fullscreen $DATA_DIR
#         ./start_measurement_glumpy.sh $ITERATIONS "${FRAMEWORKS_GLUMPY[$f]}" rects "${READERS[$r]}" fullscreen $DATA_DIR
#         ./start_measurement_glumpy.sh $ITERATIONS "${FRAMEWORKS_GLUMPY[$f]}" 3D "${READERS[$r]}" fullscreen $DATA_DIR
#         ./start_measurement_glumpy.sh $ITERATIONS "${FRAMEWORKS_GLUMPY[$f]}" image "${READERS[$r]}" fullscreen $DATA_DIR
#         ./start_measurement_glumpy.sh $ITERATIONS "${FRAMEWORKS_GLUMPY[$f]}" default "${READERS[$r]}" no_fullscreen $DATA_DIR
#         ./start_measurement_glumpy.sh $ITERATIONS "${FRAMEWORKS_GLUMPY[$f]}" default "${READERS[$r]}" small $DATA_DIR
#         r=$((r+1));
#     done
#     f=$((f+1));
# done

# final all
# for f in "${!FRAMEWORKS[@]}";
# do
#     for r in "${!READERS[@]}";
#     do
#         ./start_measurement.sh $ITERATIONS "${FRAMEWORKS[$f]}" default "${READERS[$r]}" fullscreen $DATA_DIR
#         ./start_measurement.sh $ITERATIONS "${FRAMEWORKS[$f]}" rects "${READERS[$r]}" fullscreen $DATA_DIR
#         ./start_measurement.sh $ITERATIONS "${FRAMEWORKS[$f]}" image "${READERS[$r]}" fullscreen $DATA_DIR
#         ./start_measurement.sh $ITERATIONS "${FRAMEWORKS[$f]}" 3D "${READERS[$r]}" fullscreen $DATA_DIR
#         ./start_measurement.sh $ITERATIONS "${FRAMEWORKS[$f]}" default "${READERS[$r]}" no_fullscreen $DATA_DIR
#         ./start_measurement.sh $ITERATIONS "${FRAMEWORKS[$f]}" default "${READERS[$r]}" small $DATA_DIR
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