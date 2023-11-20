#!/bin/sh

ACTION=$1
ITERATIONS=$2
TEST_PROGRAM=$3
TEST_COMPLEXITY=$4
FW_RUNNING=$5
PIXEL_READER=$6
DATA_DIR=$7


FW_PATH="framework_test_programs/$TEST_PROGRAM/${TEST_PROGRAM}_${TEST_COMPLEXITY}"

case "$TEST_PROGRAM" in 

    *"java"*)
        java ./$FW_PATH &
        PID_TEST_PROGRAM=$!
        ;;

    *"py"*)
        python ./$FW_PATH.py &
        PID_TEST_PROGRAM=$! 
        ;;

    *"tk"*)
        python ./$FW_PATH.py &
        PID_TEST_PROGRAM=$! 
        ;;
esac

sleep "1s"

sigint() {
    kill -INT $PID_TEST_PROGRAM
}

trap sigint INT

python ./fyalmd.py $ACTION $ITERATIONS $TEST_PROGRAM $TEST_COMPLEXITY $FW_RUNNING $PIXEL_READER $DATA_DIR 
PID_FYALMD=$!

kill -9 $PID_TEST_PROGRAM





