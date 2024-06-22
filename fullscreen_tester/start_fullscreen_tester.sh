#!/bin/sh

FRAMEWORKS=("Direct3D" "Direct2D" "Blend2D" "Cairo" "FLTK" "GDIplus" "GLEW" "GLUT" "GTK" "Java2D" "JavaSwing" "pygame" "pyglet" "pyqt5" "pyqt6" "Qt5" "Qt6" "pyqt6_quick" "SDL2_Software" "SDL2_OpenGL" "SDL2_OpenGLES" "SDL2_Direct3D" "SFML" "Skia" "tkinter" "wxpython" "wxpython_d2d" "WinAPI" "Unity" "Godot")
FULLSCREEN_OPTIONS=("no_fullscreen" "fullscreen")
#FULLSCREEN_OPTIONS=("small")

DATA_DIR="./data_fullscreen_states/"
FILE="./data_fullscreen_states/fse2_dse2.csv"

sleep "5s"
mkdir $DATA_DIR
touch $FILE

for fullscreen_option in "${FULLSCREEN_OPTIONS[@]}";
do
    for framework in "${FRAMEWORKS[@]}";
    do
        FW_PATH="../framework_tester_apps/$framework/${framework}_default_${fullscreen_option}"
        case "$framework" in 

            # *"psychopy"*)
            #     cd ./venv
            #     source Scripts/activate
            #     python ../$FW_PATH.py &
            #     PID_framework=$!
            #     deactivate
            #     cd ../
            #     ;;

            # *"OpenSesame_PsychoPy"*)
            #     ;;

            *"Java"*)
                java ./$FW_PATH.java &
                PID_framework=$!
                ;;

            *"py"*)
                python ./$FW_PATH.py &
                PID_framework=$! 
                ;;

            *"Skia"*)
                python ./$FW_PATH.py &
                PID_framework=$! 
                ;;

            *"tkinter"*)
                python ./$FW_PATH.py &
                PID_framework=$! 
                ;;

            *"SDL"*)
                start "./../framework_tester_apps/SDL2/${framework}_default_${fullscreen_option}.exe" &
                PID_framework=$! 
                ;;

            *"Unity"*)
                start "./../framework_tester_projects/framework_tester_applied/Unity_default/framework.exe" &
                PID_framework=$! 
                ;;

            *"Godot"*)
                start "./../framework_tester_projects/framework_tester_applied/Godot/Godot_default.exe" &
                PID_framework=$! 
                ;;

            *"UnrealEngine5"*)
                start "./../framework_tester_projects/framework_tester_applied/UnrealEngine5/out/out_default/Windows/invisible_character.exe" &
                PID_framework=$! 
                ;;

            *"Direct3D"*)
                cd "./../framework_tester_apps/Direct3D_default"
                start "./Direct3D_default_${fullscreen_option}.exe" &
                PID_framework=$! 
                cd ../../fullscreen_tester
                ;;

            *)
                start ./$FW_PATH.exe &
                PID_framework=$! 
                ;;
        esac

        sleep "5s"

        sigint() {
            kill -INT $PID_framework
        }
        trap sigint INT

        python ./fullscreen_tester.py $framework $fullscreen_option $FILE
        PID_FYALMD=$!

        kill -9 $PID_framework
        powershell kill -n "${framework}_default_${fullscreen_option}"
        powershell kill -n "${framework}_default"
        powershell kill -n "framework"
        powershell kill -n "UnrealGame"
        powershell kill -n "java"
        powershell kill -n "python"
    done
done




