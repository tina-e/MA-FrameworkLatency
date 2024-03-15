#!/bin/sh

ITERATIONS=$1
BACKEND=$2
TEST_COMPLEXITY=$3
PIXEL_READER=$4
FULLSCREEN_OPTION=$5
DATA_DIR=$6

TEST_PROGRAM="glumpy_${BACKEND}"


FW_PATH="framework_tester_${FULLSCREEN_OPTION}/glumpy/glumpy_${TEST_COMPLEXITY}"
# FW_PATH="framework_tester_fullscreen/glumpy/glumpy_${TEST_COMPLEXITY}"

python ./$FW_PATH.py --backend $BACKEND -f 0 &
PID_TEST_PROGRAM=$!

sleep "7s"

sigint() {
    kill -INT $PID_TEST_PROGRAM
}

trap sigint INT

python ./fyalmd.py $ITERATIONS $TEST_PROGRAM $TEST_COMPLEXITY $PIXEL_READER $FULLSCREEN_OPTION $DATA_DIR 
PID_FYALMD=$!

kill -9 $PID_TEST_PROGRAM
powershell kill -n "${TEST_PROGRAM}_${TEST_COMPLEXITY}"





