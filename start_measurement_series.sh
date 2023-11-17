#!/bin/sh

ITERATIONS=2
DATA_DIR="171123_measurements_test"

#mkdir "./data/$DATA_DIR"

#killall -9 picom

# ACTION = $1
# ITERATIONS = $2
# TEST_PROGRAM = $3
# TEST_COMPLEXITY = $4
# FW_RUNNING = $5
# PIXEL_READER = $6
# DATA_DIR = $7

sleep "5s"

./start_measurement.sh calibrate_and_measure $ITERATIONS pygame default True windup_python $DATA_DIR
./start_measurement.sh measure $ITERATIONS pygame default False windup_python $DATA_DIR
./start_measurement.sh measure $ITERATIONS pygame default True getpixel $DATA_DIR
./start_measurement.sh measure $ITERATIONS pygame default False getpixel $DATA_DIR
./start_measurement.sh measure $ITERATIONS pygame default True bitblt $DATA_DIR
./start_measurement.sh measure $ITERATIONS pygame default False bitblt $DATA_DIR
./start_measurement.sh measure $ITERATIONS pygame default True getdbits $DATA_DIR
./start_measurement.sh measure $ITERATIONS pygame default False getdbits $DATA_DIR

./start_measurement.sh measure $ITERATIONS pygame rects True windup_python $DATA_DIR
./start_measurement.sh measure $ITERATIONS pygame rects False windup_python $DATA_DIR
./start_measurement.sh measure $ITERATIONS pygame rects True getpixel $DATA_DIR
./start_measurement.sh measure $ITERATIONS pygame rects False getpixel $DATA_DIR
./start_measurement.sh measure $ITERATIONS pygame rects True bitblt $DATA_DIR
./start_measurement.sh measure $ITERATIONS pygame rects False bitblt $DATA_DIR
./start_measurement.sh measure $ITERATIONS pygame rects True getdbits $DATA_DIR
./start_measurement.sh measure $ITERATIONS pygame rects False getdbits $DATA_DIR


./start_measurement.sh measure $ITERATIONS pyqt5 default True windup_python $DATA_DIR
./start_measurement.sh measure $ITERATIONS pyqt5 default False windup_python $DATA_DIR
./start_measurement.sh measure $ITERATIONS pyqt5 default True getpixel $DATA_DIR
./start_measurement.sh measure $ITERATIONS pyqt5 default False getpixel $DATA_DIR
./start_measurement.sh measure $ITERATIONS pyqt5 default True bitblt $DATA_DIR
./start_measurement.sh measure $ITERATIONS pyqt5 default False bitblt $DATA_DIR
./start_measurement.sh measure $ITERATIONS pyqt5 default True getdbits $DATA_DIR
./start_measurement.sh measure $ITERATIONS pyqt5 default False getdbits $DATA_DIR

./start_measurement.sh measure $ITERATIONS pyqt5 rects True windup_python $DATA_DIR
./start_measurement.sh measure $ITERATIONS pyqt5 rects False windup_python $DATA_DIR
./start_measurement.sh measure $ITERATIONS pyqt5 rects True getpixel $DATA_DIR
./start_measurement.sh measure $ITERATIONS pyqt5 rects False getpixel $DATA_DIR
./start_measurement.sh measure $ITERATIONS pyqt5 rects True bitblt $DATA_DIR
./start_measurement.sh measure $ITERATIONS pyqt5 rects False bitblt $DATA_DIR
./start_measurement.sh measure $ITERATIONS pyqt5 rects True getdbits $DATA_DIR
./start_measurement.sh measure $ITERATIONS pyqt5 rects False getdbits $DATA_DIR


./start_measurement.sh measure $ITERATIONS tkinter default True windup_python $DATA_DIR
./start_measurement.sh measure $ITERATIONS tkinter default False windup_python $DATA_DIR
./start_measurement.sh measure $ITERATIONS tkinter default True getpixel $DATA_DIR
./start_measurement.sh measure $ITERATIONS tkinter default False getpixel $DATA_DIR
./start_measurement.sh measure $ITERATIONS tkinter default True bitblt $DATA_DIR
./start_measurement.sh measure $ITERATIONS tkinter default False bitblt $DATA_DIR
./start_measurement.sh measure $ITERATIONS tkinter default True getdbits $DATA_DIR
./start_measurement.sh measure $ITERATIONS tkinter default False getdbits $DATA_DIR

./start_measurement.sh measure $ITERATIONS tkinter rects True windup_python $DATA_DIR
./start_measurement.sh measure $ITERATIONS tkinter rects False windup_python $DATA_DIR
./start_measurement.sh measure $ITERATIONS tkinter rects True getpixel $DATA_DIR
./start_measurement.sh measure $ITERATIONS tkinter rects False getpixel $DATA_DIR
./start_measurement.sh measure $ITERATIONS tkinter rects True bitblt $DATA_DIR
./start_measurement.sh measure $ITERATIONS tkinter rects False bitblt $DATA_DIR
./start_measurement.sh measure $ITERATIONS tkinter rects True getdbits $DATA_DIR
./start_measurement.sh measure $ITERATIONS tkinter rects False getdbits $DATA_DIR


./start_measurement.sh measure $ITERATIONS javaswing default True windup_python $DATA_DIR
./start_measurement.sh measure $ITERATIONS javaswing default False windup_python $DATA_DIR
./start_measurement.sh measure $ITERATIONS javaswing default True getpixel $DATA_DIR
./start_measurement.sh measure $ITERATIONS javaswing default False getpixel $DATA_DIR
./start_measurement.sh measure $ITERATIONS javaswing default True bitblt $DATA_DIR
./start_measurement.sh measure $ITERATIONS javaswing default False bitblt $DATA_DIR
./start_measurement.sh measure $ITERATIONS javaswing default True getdbits $DATA_DIR
./start_measurement.sh measure $ITERATIONS javaswing default False getdbits $DATA_DIR

./start_measurement.sh measure $ITERATIONS javaswing rects True windup_python $DATA_DIR
./start_measurement.sh measure $ITERATIONS javaswing rects False windup_python $DATA_DIR
./start_measurement.sh measure $ITERATIONS javaswing rects True getpixel $DATA_DIR
./start_measurement.sh measure $ITERATIONS javaswing rects False getpixel $DATA_DIR
./start_measurement.sh measure $ITERATIONS javaswing rects True bitblt $DATA_DIR
./start_measurement.sh measure $ITERATIONS javaswing rects False bitblt $DATA_DIR
./start_measurement.sh measure $ITERATIONS javaswing rects True getdbits $DATA_DIR
./start_measurement.sh measure $ITERATIONS javaswing rects False getdbits $DATA_DIR

