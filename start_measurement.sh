#!/bin/sh

ACTION=$1
ITERATIONS=$2
TEST_PROGRAM=$3
TEST_COMPLEXITY=$4
FW_RUNNING=$5
PIXEL_READER=$6
DATA_DIR=$7


FW_PATH="framework_test_programs/$TEST_PROGRAM/bin/${TEST_PROGRAM}_${TEST_COMPLEXITY}"

# mkdir "./data/$DATA_DIR"

"C:\Users\Martina Emmert\AppData\Local\Programs\Python\Python38\python.exe" ./$FW_PATH &
PID_TEST_PROGRAM=$!

sleep "1s"

python ./fyalmd.py $ACTION $ITERATIONS $TEST_PROGRAM $TEST_COMPLEXITY $FW_RUNNING $PIXEL_READER $DATA_DIR &
PID_FYALMD=$!


sigint() {
    kill -INT $PID_LATENCY_TESTER
    kill -INT $PID_TEST_PROGRAM
}

trap sigint INT
wait $PID_CLICK_SIMULATOR

kill -TERM $PID_LATENCY_TESTER
kill -9 $PID_TEST_PROGRAM

# frage: stirbt das test program auch mit wenn fyalmd fertig?




