#!/bin/sh

DATA_DIR="program_tests_0305"
READERS=("windup_timestamps")
ITERATIONS=5

mkdir "./data/$DATA_DIR"
sleep "7s"


for r in "${!READERS[@]}";
do
    start ./pixel_reader_validation/test_app.exe &
    PID_TEST_APP=$! 

    sleep "1s"

    # do this in python script
    # start ./pixel_reader_validation/${READERS[$r]}.exe &
    # PID_PROGRAM=$! 

    sigint() {
        kill -INT $PID_TEST_APP
        kill -INT $PID_PROGRAM
    }
    trap sigint INT

    python ./fyalmd.py $ITERATIONS ${FRAMEWORKS[$f]} default ${READERS[$r]} fullscreen $DATA_DIR 
    PID_FYALMD=$!

    kill -9 $PID_TEST_PROGRAM
    powershell kill -n "${FRAMEWORKS[$f]}_default"
    powershell kill -n "framework"
    powershell kill -n "java"
    r=$((r+1));
done
