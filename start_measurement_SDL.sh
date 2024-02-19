#!/bin/sh

ITERATIONS=$1
TEST_PROGRAM=$2
TEST_COMPLEXITY=$3
FW_RUNNING=$4
PIXEL_READER=$5
DATA_DIR=$6

# removed "start"s to make executable from bash
FW_PATH="framework_tester_SDL/${TEST_PROGRAM}_${TEST_COMPLEXITY}"

case "$TEST_PROGRAM" in 
    *"SDL"*)
        ./$FW_PATH.exe &
        PID_TEST_PROGRAM=$! 
        ;;
esac

sleep "3s"

sigint() {
    kill -INT $PID_TEST_PROGRAM
}

trap sigint INT

python ./fyalmd.py $ITERATIONS $TEST_PROGRAM $TEST_COMPLEXITY $FW_RUNNING $PIXEL_READER $DATA_DIR 
PID_FYALMD=$!

kill -9 $PID_TEST_PROGRAM
powershell kill -n "${TEST_PROGRAM}_${TEST_COMPLEXITY}"
powershell kill -n "java"





