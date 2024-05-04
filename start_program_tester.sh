#!/bin/sh

ITERATIONS=220
DATA_DIR="program_tests_0305"

READERS=("windup_timestamps")
FRAMEWORKS=("GLEW_SDL")

mkdir "./data/$DATA_DIR"
sleep "7s"

for f in "${!FRAMEWORKS[@]}";
do
    for r in "${!READERS[@]}";
    do
        start ./framework_tester_apps/framework_tester_fullscreen/${FRAMEWORKS[$f]}/${FRAMEWORKS[$f]}_default.exe &
        PID_TEST_PROGRAM=$! 

        sleep "7s"

        sigint() {
            kill -INT $PID_TEST_PROGRAM
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
    f=$((f+1));
done