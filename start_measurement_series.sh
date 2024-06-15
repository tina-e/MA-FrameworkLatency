#!/bin/sh

ITERATIONS=200
DATA_DIR="finals_all_fix_06_1306"

READERS_ALL=("windup" "getpixel" "bitblt" "getdbits" "none")
READERS=("windup" "getpixel" "none")

# todo: direct3d check fullscreen and stuff, WinUI ohne auto
FRAMEWORKS=("Direct2D" "Blend2D" "Cairo" "FLTK" "GDIplus" "GLEW" "GLUT" "GTK" "Java2D" "JavaSwing" "pygame" "pyglet" "pyqt5" "pyqt6" "Qt5" "Qt6" "pyqt6_quick" "SDL2_Software" "SDL2_OpenGL" "SDL2_OpenGLES" "SDL2_Direct3D" "SFML" "Skia" "tkinter" "wxpython" "wxpython_d2d" "WinAPI")
FRAMEWORKS_3D=("GLEW" "GLUT" "pygame" "pyglet")


mkdir "./data/$DATA_DIR"
sleep "7s"

./start_measurement.sh $ITERATIONS FLTK image none fullscreen $DATA_DIR
./start_measurement.sh $ITERATIONS FLTK image windup fullscreen $DATA_DIR
./start_measurement.sh $ITERATIONS FLTK image getpixel fullscreen $DATA_DIR

./start_measurement.sh $ITERATIONS GLEW image none fullscreen $DATA_DIR
./start_measurement.sh $ITERATIONS GLEW image windup fullscreen $DATA_DIR
./start_measurement.sh $ITERATIONS GLEW image getpixel fullscreen $DATA_DIR

# ./start_measurement.sh $ITERATIONS Direct2D default windup fullscreen $DATA_DIR


# program validation
# for f in "${!FRAMEWORKS[@]}";
# do
#     for r in "${!READERS_ALL[@]}";
#     do
#         ./start_measurement.sh $ITERATIONS "${FRAMEWORKS[$f]}" default "${READERS_ALL[$r]}" fullscreen $DATA_DIR
#         r=$((r+1));
#     done
#     f=$((f+1));
# done

# vsync
# for f in "${!FRAMEWORKS[@]}";
# do
#     for r in "${!READERS[@]}";
#     do
#         ./start_measurement.sh $ITERATIONS "${FRAMEWORKS[$f]}" default "${READERS[$r]}" fullscreen $DATA_DIR
#         r=$((r+1));
#     done
#     f=$((f+1));
# done

# dimension
# for f in "${!FRAMEWORKS_AGAIN_2[@]}";
# do
#     for r in "${!READERS[@]}";
#     do
#         ./start_measurement.sh $ITERATIONS "${FRAMEWORKS_AGAIN_2[$f]}" default "${READERS[$r]}" large $DATA_DIR
#         ./start_measurement.sh $ITERATIONS "${FRAMEWORKS_AGAIN_2[$f]}" default "${READERS[$r]}" small $DATA_DIR
#         ./start_measurement.sh $ITERATIONS "${FRAMEWORKS_AGAIN_2[$f]}" default "${READERS[$r]}" no_fullscreen $DATA_DIR
#         r=$((r+1));
#     done
#     f=$((f+1));
# done



# complexity
# for f in "${!FRAMEWORKS_AGAIN_4[@]}";
# do
#     for r in "${!READERS[@]}";
#     do
#         ./start_measurement.sh $ITERATIONS "${FRAMEWORKS_AGAIN_4[$f]}" rects "${READERS[$r]}" fullscreen $DATA_DIR
#         ./start_measurement.sh $ITERATIONS "${FRAMEWORKS_AGAIN_4[$f]}" image "${READERS[$r]}" fullscreen $DATA_DIR
#         r=$((r+1));
#     done
#     f=$((f+1));
# done

# 3D
# for f in "${!FRAMEWORKS_3D[@]}";
# do
#     for r in "${!READERS[@]}";
#     do
#         ./start_measurement.sh $ITERATIONS "${FRAMEWORKS_3D[$f]}" 3D "${READERS[$r]}" fullscreen $DATA_DIR
#         r=$((r+1));
#     done
#     f=$((f+1));
# done


# fixes, todo
# ./start_measurement.sh $ITERATIONS GLUT 3D windup fullscreen $DATA_DIR

# ./start_measurement.sh $ITERATIONS GTK rects none fullscreen $DATA_DIR
# ./start_measurement.sh $ITERATIONS GTK rects getpixel fullscreen $DATA_DIR
# ./start_measurement.sh $ITERATIONS GTK rects windup fullscreen $DATA_DIR

# ./start_measurement.sh $ITERATIONS SFML rects windup fullscreen $DATA_DIR

# ./start_measurement.sh $ITERATIONS GLEW 3D getpixel fullscreen $DATA_DIR

# ./start_measurement.sh $ITERATIONS Direct2D default windup fullscreen $DATA_DIR


# measurements 2704 recompileds
# for f in "${!FRAMEWORKS[@]}";
# do
#     for r in "${!READERS[@]}";
#     do
#         #./start_measurement.sh $ITERATIONS "${FRAMEWORKS_BIG[$f]}" default "${READERS[$r]}" big $DATA_DIR
#         #./start_measurement.sh $ITERATIONS "${FRAMEWORKS_BIG[$f]}" default "${READERS[$r]}" small $DATA_DIR
#         #./start_measurement.sh $ITERATIONS "${FRAMEWORKS_BIG[$f]}" default "${READERS[$r]}" no_fullscreen $DATA_DIR
#         ./start_measurement.sh $ITERATIONS "${FRAMEWORKS[$f]}" image "${READERS[$r]}" fullscreen $DATA_DIR
#         r=$((r+1));
#     done
#     f=$((f+1));
# done
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
#     ./start_measurement.sh $ITERATIONS win32 default "${READERS[$r]}" small $DATA_DIR
#     ./start_measurement.sh $ITERATIONS win32 rects "${READERS[$r]}" big $DATA_DIR
#     ./start_measurement.sh $ITERATIONS win32 rects "${READERS[$r]}" no_fullscreen $DATA_DIR
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

# for r in "${!READERS[@]}";
# do
#     ./start_measurement.sh $ITERATIONS Skia default "${READERS[$r]}" no_fullscreen $DATA_DIR
#     ./start_measurement.sh $ITERATIONS Skia rects "${READERS[$r]}" no_fullscreen $DATA_DIR
#     r=$((r+1));
# done

# no auto start opensesame
# sleep "10s"
# ./start_measurement.sh $ITERATIONS EPrime rects windup fullscreen $DATA_DIR
# ./start_measurement.sh $ITERATIONS EPrime rects getpixel fullscreen $DATA_DIR
# ./start_measurement.sh $ITERATIONS EPrime rects none fullscreen $DATA_DIR
