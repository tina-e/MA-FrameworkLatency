#!/bin/sh

ITERATIONS=50
DATA_DIR="glumpy_291123"

mkdir "./data/$DATA_DIR"

sleep "5s"


./start_measurement.sh calibrate_and_measure $ITERATIONS pyglet default True windup_python $DATA_DIR
./start_measurement.sh calibrate_and_measure $ITERATIONS pyglet default False windup_python $DATA_DIR

./start_measurement.sh calibrate_and_measure $ITERATIONS pyglet default True getpixel $DATA_DIR
./start_measurement.sh calibrate_and_measure $ITERATIONS pyglet default False getpixel $DATA_DIR

./start_measurement.sh calibrate_and_measure $ITERATIONS pyglet default True bitblt $DATA_DIR
./start_measurement.sh calibrate_and_measure $ITERATIONS pyglet default False bitblt $DATA_DIR

./start_measurement.sh calibrate_and_measure $ITERATIONS pyglet default True getdbits $DATA_DIR
./start_measurement.sh calibrate_and_measure $ITERATIONS pyglet default False getdbits $DATA_DIR



./start_measurement.sh calibrate_and_measure $ITERATIONS pyglet rects True windup_python $DATA_DIR
./start_measurement.sh calibrate_and_measure $ITERATIONS pyglet rects False windup_python $DATA_DIR

./start_measurement.sh calibrate_and_measure $ITERATIONS pyglet rects True getpixel $DATA_DIR
./start_measurement.sh calibrate_and_measure $ITERATIONS pyglet rects False getpixel $DATA_DIR

./start_measurement.sh calibrate_and_measure $ITERATIONS pyglet rects True bitblt $DATA_DIR
./start_measurement.sh calibrate_and_measure $ITERATIONS pyglet rects False bitblt $DATA_DIR

./start_measurement.sh calibrate_and_measure $ITERATIONS pyglet rects True getdbits $DATA_DIR
./start_measurement.sh calibrate_and_measure $ITERATIONS pyglet rects False getdbits $DATA_DIR




./start_measurement.sh calibrate_and_measure $ITERATIONS glfw default True windup_python $DATA_DIR
./start_measurement.sh calibrate_and_measure $ITERATIONS glfw default False windup_python $DATA_DIR
./start_measurement.sh calibrate_and_measure $ITERATIONS glfw default True getpixel $DATA_DIR
./start_measurement.sh calibrate_and_measure $ITERATIONS glfw default False getpixel $DATA_DIR
./start_measurement.sh calibrate_and_measure $ITERATIONS glfw default True bitblt $DATA_DIR
./start_measurement.sh calibrate_and_measure $ITERATIONS glfw default False bitblt $DATA_DIR
./start_measurement.sh calibrate_and_measure $ITERATIONS glfw default True getdbits $DATA_DIR
./start_measurement.sh calibrate_and_measure $ITERATIONS glfw default False getdbits $DATA_DIR
./start_measurement.sh calibrate_and_measure $ITERATIONS glfw rects True windup_python $DATA_DIR
./start_measurement.sh calibrate_and_measure $ITERATIONS glfw rects False windup_python $DATA_DIR
./start_measurement.sh calibrate_and_measure $ITERATIONS glfw rects True getpixel $DATA_DIR
./start_measurement.sh calibrate_and_measure $ITERATIONS glfw rects False getpixel $DATA_DIR
./start_measurement.sh calibrate_and_measure $ITERATIONS glfw rects True bitblt $DATA_DIR
./start_measurement.sh calibrate_and_measure $ITERATIONS glfw rects False bitblt $DATA_DIR
./start_measurement.sh calibrate_and_measure $ITERATIONS glfw rects True getdbits $DATA_DIR
./start_measurement.sh calibrate_and_measure $ITERATIONS glfw rects False getdbits $DATA_DIR


./start_measurement.sh calibrate_and_measure $ITERATIONS sdl default True windup_python $DATA_DIR
./start_measurement.sh calibrate_and_measure $ITERATIONS sdl default False windup_python $DATA_DIR
./start_measurement.sh calibrate_and_measure $ITERATIONS sdl default True getpixel $DATA_DIR
./start_measurement.sh calibrate_and_measure $ITERATIONS sdl default False getpixel $DATA_DIR
./start_measurement.sh calibrate_and_measure $ITERATIONS sdl default True bitblt $DATA_DIR
./start_measurement.sh calibrate_and_measure $ITERATIONS sdl default False bitblt $DATA_DIR
./start_measurement.sh calibrate_and_measure $ITERATIONS sdl default True getdbits $DATA_DIR
./start_measurement.sh calibrate_and_measure $ITERATIONS sdl default False getdbits $DATA_DIR
./start_measurement.sh calibrate_and_measure $ITERATIONS sdl rects True windup_python $DATA_DIR
./start_measurement.sh calibrate_and_measure $ITERATIONS sdl rects False windup_python $DATA_DIR
./start_measurement.sh calibrate_and_measure $ITERATIONS sdl rects True getpixel $DATA_DIR
./start_measurement.sh calibrate_and_measure $ITERATIONS sdl rects False getpixel $DATA_DIR
./start_measurement.sh calibrate_and_measure $ITERATIONS sdl rects True bitblt $DATA_DIR
./start_measurement.sh calibrate_and_measure $ITERATIONS sdl rects False bitblt $DATA_DIR
./start_measurement.sh calibrate_and_measure $ITERATIONS sdl rects True getdbits $DATA_DIR
./start_measurement.sh calibrate_and_measure $ITERATIONS sdl rects False getdbits $DATA_DIR


./start_measurement.sh calibrate_and_measure $ITERATIONS freeglut default True windup_python $DATA_DIR
./start_measurement.sh calibrate_and_measure $ITERATIONS freeglut default False windup_python $DATA_DIR
./start_measurement.sh calibrate_and_measure $ITERATIONS freeglut default True getpixel $DATA_DIR
./start_measurement.sh calibrate_and_measure $ITERATIONS freeglut default False getpixel $DATA_DIR
./start_measurement.sh calibrate_and_measure $ITERATIONS freeglut default True bitblt $DATA_DIR
./start_measurement.sh calibrate_and_measure $ITERATIONS freeglut default False bitblt $DATA_DIR
./start_measurement.sh calibrate_and_measure $ITERATIONS freeglut default True getdbits $DATA_DIR
./start_measurement.sh calibrate_and_measure $ITERATIONS freeglut default False getdbits $DATA_DIR
./start_measurement.sh calibrate_and_measure $ITERATIONS freeglut rects True windup_python $DATA_DIR
./start_measurement.sh calibrate_and_measure $ITERATIONS freeglut rects False windup_python $DATA_DIR
./start_measurement.sh calibrate_and_measure $ITERATIONS freeglut rects True getpixel $DATA_DIR
./start_measurement.sh calibrate_and_measure $ITERATIONS freeglut rects False getpixel $DATA_DIR
./start_measurement.sh calibrate_and_measure $ITERATIONS freeglut rects True bitblt $DATA_DIR
./start_measurement.sh calibrate_and_measure $ITERATIONS freeglut rects False bitblt $DATA_DIR
./start_measurement.sh calibrate_and_measure $ITERATIONS freeglut rects True getdbits $DATA_DIR
./start_measurement.sh calibrate_and_measure $ITERATIONS freeglut rects False getdbits $DATA_DIR


./start_measurement.sh calibrate_and_measure $ITERATIONS qt5 default True windup_python $DATA_DIR
./start_measurement.sh calibrate_and_measure $ITERATIONS qt5 default False windup_python $DATA_DIR
./start_measurement.sh calibrate_and_measure $ITERATIONS qt5 default True getpixel $DATA_DIR
./start_measurement.sh calibrate_and_measure $ITERATIONS qt5 default False getpixel $DATA_DIR
./start_measurement.sh calibrate_and_measure $ITERATIONS qt5 default True bitblt $DATA_DIR
./start_measurement.sh calibrate_and_measure $ITERATIONS qt5 default False bitblt $DATA_DIR
./start_measurement.sh calibrate_and_measure $ITERATIONS qt5 default True getdbits $DATA_DIR
./start_measurement.sh calibrate_and_measure $ITERATIONS qt5 default False getdbits $DATA_DIR
./start_measurement.sh calibrate_and_measure $ITERATIONS qt5 rects True windup_python $DATA_DIR
./start_measurement.sh calibrate_and_measure $ITERATIONS qt5 rects False windup_python $DATA_DIR
./start_measurement.sh calibrate_and_measure $ITERATIONS qt5 rects True getpixel $DATA_DIR
./start_measurement.sh calibrate_and_measure $ITERATIONS qt5 rects False getpixel $DATA_DIR
./start_measurement.sh calibrate_and_measure $ITERATIONS qt5 rects True bitblt $DATA_DIR
./start_measurement.sh calibrate_and_measure $ITERATIONS qt5 rects False bitblt $DATA_DIR
./start_measurement.sh calibrate_and_measure $ITERATIONS qt5 rects True getdbits $DATA_DIR
./start_measurement.sh calibrate_and_measure $ITERATIONS qt5 rects False getdbits $DATA_DIR
