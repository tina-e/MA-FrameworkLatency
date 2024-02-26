#!/bin/sh

ITERATIONS=$1
TEST_PROGRAM=$2
TEST_COMPLEXITY=$3
FW_RUNNING=$4
PIXEL_READER=$5
DATA_DIR=$6


FW_PATH="framework_tester_fullscreen/$TEST_PROGRAM/${TEST_PROGRAM}_${TEST_COMPLEXITY}"

case "$TEST_PROGRAM" in 

    *"psychopy"*)
        cd ./venv
        source Scripts/activate
        python ../$FW_PATH.py &
        PID_TEST_PROGRAM=$!
        deactivate
        cd ../
        ;;

    *"Java"*)
        java ./$FW_PATH.java &
        PID_TEST_PROGRAM=$!
        ;;

    *"py"*)
        python ./$FW_PATH.py &
        PID_TEST_PROGRAM=$! 
        ;;

    *"tkinter"*)
        python ./$FW_PATH.py &
        PID_TEST_PROGRAM=$! 
        ;;

    *"SDL"*)
        start ./$FW_PATH.exe &
        PID_TEST_PROGRAM=$! 
        ;;

    *"GLUT"*)
        start ./$FW_PATH.exe &
        PID_TEST_PROGRAM=$! 
        ;;

    *"GLEW"*)
        start ./$FW_PATH.exe &
        PID_TEST_PROGRAM=$! 
        ;;

    *"GTK"*)
        #set GDK_BACKEND=win32
        set GDK_BACKEND=OpenGL #????
        start ./$FW_PATH.exe &
        PID_TEST_PROGRAM=$! 
        ;;

    *"FLTK"*)
        ./$FW_PATH.exe &
        PID_TEST_PROGRAM=$! 
        ;;

    *"win32"*)
        start ./$FW_PATH.exe &
        PID_TEST_PROGRAM=$! 
        ;;

    *"Godot"*)
        start ./framework_tester_fullscreen/GameEngines/$TEST_PROGRAM/${TEST_PROGRAM}_${TEST_COMPLEXITY}.exe &
        PID_TEST_PROGRAM=$!
        ;;

    *"Unity"*)
        start ./framework_tester_fullscreen/${TEST_PROGRAM}_${TEST_COMPLEXITY}/framework.exe &
        PID_TEST_PROGRAM=$!
        ;;

    *"DirectX"*)
        cd "./framework_tester_fullscreen/${TEST_PROGRAM}_${TEST_COMPLEXITY}"
        start "./${TEST_PROGRAM}_${TEST_COMPLEXITY}.exe" &
        PID_TEST_PROGRAM=$! 
        cd "../../"
        ;;

    *"Qt"*)
        start ./framework_tester_fullscreen/${TEST_PROGRAM}_${TEST_COMPLEXITY}/${TEST_PROGRAM}_${TEST_COMPLEXITY}.exe &
        PID_TEST_PROGRAM=$! 
        ;;

esac

sleep "7s"

sigint() {
    kill -INT $PID_TEST_PROGRAM
}

trap sigint INT

python ./fyalmd.py $ITERATIONS $TEST_PROGRAM $TEST_COMPLEXITY $FW_RUNNING $PIXEL_READER $DATA_DIR 
PID_FYALMD=$!

kill -9 $PID_TEST_PROGRAM
powershell kill -n "${TEST_PROGRAM}_${TEST_COMPLEXITY}"
powershell kill -n "framework"
powershell kill -n "java"





