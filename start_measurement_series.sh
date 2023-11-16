#!/bin/sh

ITERATIONS=200
DATA_DIR="161123_measurements_2"


#killall -9 picom

# ACTION = $1
# ITERATIONS = $2
# TEST_PROGRAM = $3
# TEST_COMPLEXITY = $4
# FW_RUNNING = $5
# PIXEL_READER = $6
# DATA_DIR = $7

sleep "10s"

./start_measurement.sh calibrate_and_measure $ITERATIONS pyglet default True windup_python $DATA_DIR
./start_measurement.sh measure $ITERATIONS pyglet default False windup_python $DATA_DIR
./start_measurement.sh measure $ITERATIONS pyglet default True getpixel $DATA_DIR
./start_measurement.sh measure $ITERATIONS pyglet default False getpixel $DATA_DIR
./start_measurement.sh measure $ITERATIONS pyglet default True bitblt $DATA_DIR
./start_measurement.sh measure $ITERATIONS pyglet default False bitblt $DATA_DIR
./start_measurement.sh measure $ITERATIONS pyglet default True getdbits $DATA_DIR
./start_measurement.sh measure $ITERATIONS pyglet default False getdbits $DATA_DIR

./start_measurement.sh measure $ITERATIONS pyglet rects True windup_python $DATA_DIR
./start_measurement.sh measure $ITERATIONS pyglet rects False windup_python $DATA_DIR
./start_measurement.sh measure $ITERATIONS pyglet rects True getpixel $DATA_DIR
./start_measurement.sh measure $ITERATIONS pyglet rects False getpixel $DATA_DIR
./start_measurement.sh measure $ITERATIONS pyglet rects True bitblt $DATA_DIR
./start_measurement.sh measure $ITERATIONS pyglet rects False bitblt $DATA_DIR
./start_measurement.sh measure $ITERATIONS pyglet rects True getdbits $DATA_DIR
./start_measurement.sh measure $ITERATIONS pyglet rects False getdbits $DATA_DIR

