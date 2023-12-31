#!/bin/sh

ACTION=$1
ITERATIONS=$2
BACKEND=$3
TEST_COMPLEXITY=$4
FW_RUNNING=$5
PIXEL_READER=$6
DATA_DIR=$7

TEST_PROGRAM="glumpy_${BACKEND}"


FW_PATH="framework_tester/glumpy/glumpy_${TEST_COMPLEXITY}"

python ./$FW_PATH.py --backend $BACKEND -f 0 &
PID_TEST_PROGRAM=$!

sleep "2s"

sigint() {
    kill -INT $PID_TEST_PROGRAM
}

trap sigint INT

python ./fyalmd.py $ACTION $ITERATIONS $TEST_PROGRAM $TEST_COMPLEXITY $FW_RUNNING $PIXEL_READER $DATA_DIR 
PID_FYALMD=$!

kill -9 $PID_TEST_PROGRAM
powershell kill -n "${TEST_PROGRAM}_${TEST_COMPLEXITY}"





