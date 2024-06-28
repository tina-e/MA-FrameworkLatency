#!/bin/sh

ITERATIONS=$1
TEST_APP=$2
TEST_COMPLEXITY=$3
PIXEL_READER=$4
FULLSCREEN_OPTION=$5
DATA_DIR=$6


FW_PATH="framework_tester_apps/$TEST_APP/${TEST_APP}_${TEST_COMPLEXITY}_${FULLSCREEN_OPTION}"

case "$TEST_APP" in 

    # *"psychopy"*)
    #     cd ./framework_tester_projects/framework_tester_applied/psychopy/psychopy_venv
    #     source ./Scripts/activate
    #     python ../psychopy_${TEST_COMPLEXITY}.py &
    #     PID_TEST_PROGRAM=$!
    #     # deactivate
    #     cd ../../../../
    #     ;;

    # *"OpenSesame_PsychoPy"*)
    #     ;;

    # *"Java"*)
    #     java ./$FW_PATH.java &
    #     PID_TEST_APP=$!
    #     ;;

    # *"py"*)
    #     python ./$FW_PATH.py &
    #     PID_TEST_APP=$! 
    #     ;;

    # *"Skia"*)
    #     python ./$FW_PATH.py &
    #     PID_TEST_APP=$! 
    #     ;;

    # *"tkinter"*)
    #     python ./$FW_PATH.py &
    #     PID_TEST_APP=$! 
    #     ;;

    # *"SDL"*)
    #     start "./framework_tester_apps/SDL2/${TEST_APP}_${TEST_COMPLEXITY}_${FULLSCREEN_OPTION}.exe" &
    #     PID_TEST_APP=$! 
    #     ;;

    # *"Unity"*)
    #     start "./framework_tester_projects/framework_tester_applied/Unity_${TEST_COMPLEXITY}/framework.exe" &
    #     PID_TEST_APP=$! 
    #     ;;

    # *"Godot"*)
    #     start "./framework_tester_projects/framework_tester_applied/Godot/Godot_${TEST_COMPLEXITY}.exe" &
    #     PID_TEST_APP=$! 
    #     ;;

    # *"UnrealEngine5"*)
    #     start "./framework_tester_projects/framework_tester_applied/UnrealEngine5/out/out_${TEST_COMPLEXITY}/Windows/invisible_character.exe" &
    #     PID_TEST_APP=$! 
    #     ;;

    # *"Direct3D"*)
    #     cd "./framework_tester_apps/Direct3D_${TEST_COMPLEXITY}"
    #     start "./Direct3D_${TEST_COMPLEXITY}_${FULLSCREEN_OPTION}.exe" &
    #     PID_TEST_APP=$! 
    #     cd ../../
    #     ;;

    # *)
    #     start ./$FW_PATH.exe &
    #     PID_TEST_APP=$! 
    #     ;;

esac

sleep "7s"

sigint() {
    kill -INT $PID_TEST_APP
}

trap sigint INT

python ./fyalmd.py $ITERATIONS $TEST_APP $TEST_COMPLEXITY $PIXEL_READER $FULLSCREEN_OPTION $DATA_DIR 
PID_FYALMD=$!

# TSKILL $PID_TEST_APP
# # kill -9 $PID_TEST_APP
# powershell kill -n "${TEST_APP}_${TEST_COMPLEXITY}_${FULLSCREEN_OPTION}"
# powershell kill -n "${TEST_APP}_${TEST_COMPLEXITY}"
# powershell kill -n "framework"
# powershell kill -n "UnrealGame"
# powershell kill -n "java"
# powershell kill -n "python"

# cd ./framework_tester_projects/framework_tester_applied/psychopy/psychopy_venv
# deactivate
# cd ../../../../



