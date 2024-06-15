#!/bin/sh

ITERATIONS=$1
TEST_APP=$2
TEST_COMPLEXITY=$3
PIXEL_READER=$4
FULLSCREEN_OPTION=$5
DATA_DIR=$6


#  *"psychopy"*)
#         cd ./venv
#         source Scripts/activate
#         python ../$FW_PATH.py &
#         PID_TEST_PROGRAM=$!
#         deactivate
#         cd ../
#         ;;

FW_PATH="framework_tester_apps/$TEST_APP/${TEST_APP}_${TEST_COMPLEXITY}_${FULLSCREEN_OPTION}"

case "$TEST_APP" in 

    *"OpenSesame_PsychoPy"*)
        ;;

    *"Java"*)
        java ./$FW_PATH.java &
        PID_TEST_APP=$!
        ;;

    *"py"*)
        python ./$FW_PATH.py &
        PID_TEST_APP=$! 
        ;;

    *"Skia"*)
        python ./$FW_PATH.py &
        PID_TEST_APP=$! 
        ;;

    *"tkinter"*)
        python ./$FW_PATH.py &
        PID_TEST_APP=$! 
        ;;

    *"SDL"*)
        start "./framework_tester_apps/SDL2/${TEST_APP}_${TEST_COMPLEXITY}_${FULLSCREEN_OPTION}.exe" &
        PID_TEST_APP=$! 
        ;;

    *)
        start ./$FW_PATH.exe &
        PID_TEST_APP=$! 
        ;;

esac

sleep "7s"

sigint() {
    kill -INT $PID_TEST_APP
}

trap sigint INT

python ./fyalmd.py $ITERATIONS $TEST_APP $TEST_COMPLEXITY $PIXEL_READER $FULLSCREEN_OPTION $DATA_DIR 
PID_FYALMD=$!

TSKILL $PID_TEST_APP
# kill -9 $PID_TEST_APP
powershell kill -n "${TEST_APP}_${TEST_COMPLEXITY}_${FULLSCREEN_OPTION}"
powershell kill -n "framework"
powershell kill -n "java"
powershell kill -n "python"





