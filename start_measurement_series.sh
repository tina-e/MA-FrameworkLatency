#!/bin/sh

ITERATIONS=50
DATA_DIR="480hz_test"

mkdir "./data/$DATA_DIR"

#killall -9 picom

# ACTION = $1
# ITERATIONS = $2
# TEST_PROGRAM = $3
# TEST_COMPLEXITY = $4
# FW_RUNNING = $5
# PIXEL_READER = $6
# DATA_DIR = $7

sleep "5s"

# # SDL2 ---------------------------------------------------------------------------------------
# ./start_measurement.sh calibrate_and_measure $ITERATIONS SDL2_Software default False windup_python $DATA_DIR

# ./start_measurement.sh measure $ITERATIONS SDL2_OPENGL default True windup_python $DATA_DIR
# ./start_measurement.sh measure $ITERATIONS SDL2_OPENGL default False windup_python $DATA_DIR
# ./start_measurement.sh measure $ITERATIONS SDL2_OpenGLES default True windup_python $DATA_DIR
# ./start_measurement.sh measure $ITERATIONS SDL2_OpenGLES default False windup_python $DATA_DIR
# ./start_measurement.sh measure $ITERATIONS SDL2_OPENGL rects True windup_python $DATA_DIR
# ./start_measurement.sh measure $ITERATIONS SDL2_OPENGL rects False windup_python $DATA_DIR
# ./start_measurement.sh measure $ITERATIONS SDL2_OpenGLES rects True windup_python $DATA_DIR
# ./start_measurement.sh measure $ITERATIONS SDL2_OpenGLES rects False windup_python $DATA_DIR

# ./start_measurement.sh measure $ITERATIONS SDL2_Software default False getpixel $DATA_DIR
# ./start_measurement.sh measure $ITERATIONS SDL2_Software default True windup_python $DATA_DIR
# ./start_measurement.sh measure $ITERATIONS SDL2_Software default False windup_python $DATA_DIR
# ./start_measurement.sh measure $ITERATIONS SDL2_Software default True bitblt $DATA_DIR
# ./start_measurement.sh measure $ITERATIONS SDL2_Software default False bitblt $DATA_DIR
# ./start_measurement.sh measure $ITERATIONS SDL2_Software default True getdbits $DATA_DIR
# ./start_measurement.sh measure $ITERATIONS SDL2_Software default False getdbits $DATA_DIR

# ./start_measurement.sh measure $ITERATIONS SDL2_OPENGL default True getpixel $DATA_DIR
# ./start_measurement.sh measure $ITERATIONS SDL2_OPENGL default False getpixel $DATA_DIR
# ./start_measurement.sh measure $ITERATIONS SDL2_OPENGL default True bitblt $DATA_DIR
# ./start_measurement.sh measure $ITERATIONS SDL2_OPENGL default False bitblt $DATA_DIR
# ./start_measurement.sh measure $ITERATIONS SDL2_OPENGL default True getdbits $DATA_DIR
# ./start_measurement.sh measure $ITERATIONS SDL2_OPENGL default False getdbits $DATA_DIR

# ./start_measurement.sh measure $ITERATIONS SDL2_OpenGLES default True getpixel $DATA_DIR
# ./start_measurement.sh measure $ITERATIONS SDL2_OpenGLES default False getpixel $DATA_DIR
# ./start_measurement.sh measure $ITERATIONS SDL2_OpenGLES default True bitblt $DATA_DIR
# ./start_measurement.sh measure $ITERATIONS SDL2_OpenGLES default False bitblt $DATA_DIR
# ./start_measurement.sh measure $ITERATIONS SDL2_OpenGLES default True getdbits $DATA_DIR
# ./start_measurement.sh measure $ITERATIONS SDL2_OpenGLES default False getdbits $DATA_DIR

# ./start_measurement.sh measure $ITERATIONS SDL2_Software rects True getpixel $DATA_DIR
# ./start_measurement.sh measure $ITERATIONS SDL2_Software rects False getpixel $DATA_DIR
# ./start_measurement.sh measure $ITERATIONS SDL2_Software rects True windup_python $DATA_DIR
# ./start_measurement.sh measure $ITERATIONS SDL2_Software rects False windup_python $DATA_DIR
# ./start_measurement.sh measure $ITERATIONS SDL2_Software rects True bitblt $DATA_DIR
# ./start_measurement.sh measure $ITERATIONS SDL2_Software rects False bitblt $DATA_DIR
# ./start_measurement.sh measure $ITERATIONS SDL2_Software rects True getdbits $DATA_DIR
# ./start_measurement.sh measure $ITERATIONS SDL2_Software rects False getdbits $DATA_DIR

# ./start_measurement.sh measure $ITERATIONS SDL2_OPENGL rects True getpixel $DATA_DIR
# ./start_measurement.sh measure $ITERATIONS SDL2_OPENGL rects False getpixel $DATA_DIR
# ./start_measurement.sh measure $ITERATIONS SDL2_OPENGL rects True bitblt $DATA_DIR
# ./start_measurement.sh measure $ITERATIONS SDL2_OPENGL rects False bitblt $DATA_DIR
# ./start_measurement.sh measure $ITERATIONS SDL2_OPENGL rects True getdbits $DATA_DIR
# ./start_measurement.sh measure $ITERATIONS SDL2_OPENGL rects False getdbits $DATA_DIR

# ./start_measurement.sh measure $ITERATIONS SDL2_OpenGLES rects True getpixel $DATA_DIR
# ./start_measurement.sh measure $ITERATIONS SDL2_OpenGLES rects False getpixel $DATA_DIR
# ./start_measurement.sh measure $ITERATIONS SDL2_OpenGLES rects True bitblt $DATA_DIR
# ./start_measurement.sh measure $ITERATIONS SDL2_OpenGLES rects False bitblt $DATA_DIR
# ./start_measurement.sh measure $ITERATIONS SDL2_OpenGLES rects True getdbits $DATA_DIR
# ./start_measurement.sh measure $ITERATIONS SDL2_OpenGLES rects False getdbits $DATA_DIR


# # # pygame ---------------------------------------------------------------------------------------
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

# # # wxpython ---------------------------------------------------------------------------------------
# ./start_measurement.sh measure $ITERATIONS wxpython default True windup_python $DATA_DIR
# ./start_measurement.sh measure $ITERATIONS wxpython default False windup_python $DATA_DIR
# ./start_measurement.sh measure $ITERATIONS wxpython default True getpixel $DATA_DIR
# ./start_measurement.sh measure $ITERATIONS wxpython default False getpixel $DATA_DIR
# ./start_measurement.sh measure $ITERATIONS wxpython default True bitblt $DATA_DIR
# ./start_measurement.sh measure $ITERATIONS wxpython default False bitblt $DATA_DIR
# ./start_measurement.sh measure $ITERATIONS wxpython default True getdbits $DATA_DIR
# ./start_measurement.sh measure $ITERATIONS wxpython default False getdbits $DATA_DIR

# ./start_measurement.sh measure $ITERATIONS wxpython rects True windup_python $DATA_DIR
# ./start_measurement.sh measure $ITERATIONS wxpython rects False windup_python $DATA_DIR
# ./start_measurement.sh measure $ITERATIONS wxpython rects True getpixel $DATA_DIR
# ./start_measurement.sh measure $ITERATIONS wxpython rects False getpixel $DATA_DIR
# ./start_measurement.sh measure $ITERATIONS wxpython rects True bitblt $DATA_DIR
# ./start_measurement.sh measure $ITERATIONS wxpython rects False bitblt $DATA_DIR
# ./start_measurement.sh measure $ITERATIONS wxpython rects True getdbits $DATA_DIR
# ./start_measurement.sh measure $ITERATIONS wxpython rects False getdbits $DATA_DIR

# # # pyqt5 ---------------------------------------------------------------------------------------
# ./start_measurement.sh measure $ITERATIONS pyqt5 default True windup_python $DATA_DIR
# ./start_measurement.sh measure $ITERATIONS pyqt5 default False windup_python $DATA_DIR
# ./start_measurement.sh measure $ITERATIONS pyqt5 default True getpixel $DATA_DIR
# ./start_measurement.sh measure $ITERATIONS pyqt5 default False getpixel $DATA_DIR
# ./start_measurement.sh measure $ITERATIONS pyqt5 default True bitblt $DATA_DIR
# ./start_measurement.sh measure $ITERATIONS pyqt5 default False bitblt $DATA_DIR
# ./start_measurement.sh measure $ITERATIONS pyqt5 default True getdbits $DATA_DIR
# ./start_measurement.sh measure $ITERATIONS pyqt5 default False getdbits $DATA_DIR

# ./start_measurement.sh measure $ITERATIONS pyqt5 rects True windup_python $DATA_DIR
# ./start_measurement.sh measure $ITERATIONS pyqt5 rects False windup_python $DATA_DIR
# ./start_measurement.sh measure $ITERATIONS pyqt5 rects True getpixel $DATA_DIR
# ./start_measurement.sh measure $ITERATIONS pyqt5 rects False getpixel $DATA_DIR
# ./start_measurement.sh measure $ITERATIONS pyqt5 rects True bitblt $DATA_DIR
# ./start_measurement.sh measure $ITERATIONS pyqt5 rects False bitblt $DATA_DIR
# ./start_measurement.sh measure $ITERATIONS pyqt5 rects True getdbits $DATA_DIR
# ./start_measurement.sh measure $ITERATIONS pyqt5 rects False getdbits $DATA_DIR

# # # tkinter ---------------------------------------------------------------------------------------
# ./start_measurement.sh measure $ITERATIONS tkinter default True windup_python $DATA_DIR
# ./start_measurement.sh measure $ITERATIONS tkinter default False windup_python $DATA_DIR
# ./start_measurement.sh measure $ITERATIONS tkinter default True getpixel $DATA_DIR
# ./start_measurement.sh measure $ITERATIONS tkinter default False getpixel $DATA_DIR
# ./start_measurement.sh measure $ITERATIONS tkinter default True bitblt $DATA_DIR
# ./start_measurement.sh measure $ITERATIONS tkinter default False bitblt $DATA_DIR
# ./start_measurement.sh measure $ITERATIONS tkinter default True getdbits $DATA_DIR
# ./start_measurement.sh measure $ITERATIONS tkinter default False getdbits $DATA_DIR

# ./start_measurement.sh measure $ITERATIONS tkinter rects True windup_python $DATA_DIR
# ./start_measurement.sh measure $ITERATIONS tkinter rects False windup_python $DATA_DIR
# ./start_measurement.sh measure $ITERATIONS tkinter rects True getpixel $DATA_DIR
# ./start_measurement.sh measure $ITERATIONS tkinter rects False getpixel $DATA_DIR
# ./start_measurement.sh measure $ITERATIONS tkinter rects True bitblt $DATA_DIR
# ./start_measurement.sh measure $ITERATIONS tkinter rects False bitblt $DATA_DIR
# ./start_measurement.sh measure $ITERATIONS tkinter rects True getdbits $DATA_DIR
# ./start_measurement.sh measure $ITERATIONS tkinter rects False getdbits $DATA_DIR

# # JavaSwing ---------------------------------------------------------------------------------------
# ./start_measurement.sh measure $ITERATIONS JavaSwing default True getpixel $DATA_DIR
# ./start_measurement.sh measure $ITERATIONS JavaSwing default False getpixel $DATA_DIR
# ./start_measurement.sh measure $ITERATIONS JavaSwing default True windup_python $DATA_DIR
# ./start_measurement.sh measure $ITERATIONS JavaSwing default False windup_python $DATA_DIR
# ./start_measurement.sh measure $ITERATIONS JavaSwing default True bitblt $DATA_DIR
# ./start_measurement.sh measure $ITERATIONS JavaSwing default False bitblt $DATA_DIR
# ./start_measurement.sh measure $ITERATIONS JavaSwing default True getdbits $DATA_DIR
# ./start_measurement.sh measure $ITERATIONS JavaSwing default False getdbits $DATA_DIR

# ./start_measurement.sh measure $ITERATIONS JavaSwing rects True windup_python $DATA_DIR
# ./start_measurement.sh measure $ITERATIONS JavaSwing rects False windup_python $DATA_DIR
# ./start_measurement.sh measure $ITERATIONS JavaSwing rects True getpixel $DATA_DIR
# ./start_measurement.sh measure $ITERATIONS JavaSwing rects False getpixel $DATA_DIR
# ./start_measurement.sh measure $ITERATIONS JavaSwing rects True bitblt $DATA_DIR
# ./start_measurement.sh measure $ITERATIONS JavaSwing rects False bitblt $DATA_DIR
# ./start_measurement.sh measure $ITERATIONS JavaSwing rects True getdbits $DATA_DIR
# ./start_measurement.sh measure $ITERATIONS JavaSwing rects False getdbits $DATA_DIR

# # Java2D ---------------------------------------------------------------------------------------
# ./start_measurement.sh measure $ITERATIONS Java2D default True windup_python $DATA_DIR
# ./start_measurement.sh measure $ITERATIONS Java2D default False windup_python $DATA_DIR
# ./start_measurement.sh measure $ITERATIONS Java2D default True getpixel $DATA_DIR
# ./start_measurement.sh measure $ITERATIONS Java2D default False getpixel $DATA_DIR
# ./start_measurement.sh measure $ITERATIONS Java2D default True bitblt $DATA_DIR
# ./start_measurement.sh measure $ITERATIONS Java2D default False bitblt $DATA_DIR
# ./start_measurement.sh measure $ITERATIONS Java2D default True getdbits $DATA_DIR
# ./start_measurement.sh measure $ITERATIONS Java2D default False getdbits $DATA_DIR

# ./start_measurement.sh measure $ITERATIONS Java2D rects True windup_python $DATA_DIR
# ./start_measurement.sh measure $ITERATIONS Java2D rects False windup_python $DATA_DIR
# ./start_measurement.sh measure $ITERATIONS Java2D rects True getpixel $DATA_DIR
# ./start_measurement.sh measure $ITERATIONS Java2D rects False getpixel $DATA_DIR
# ./start_measurement.sh measure $ITERATIONS Java2D rects True bitblt $DATA_DIR
# ./start_measurement.sh measure $ITERATIONS Java2D rects False bitblt $DATA_DIR
# ./start_measurement.sh measure $ITERATIONS Java2D rects True getdbits $DATA_DIR
# ./start_measurement.sh measure $ITERATIONS Java2D rects False getdbits $DATA_DIR
