#!/bin/sh

FRAMEWORKS=("FLTK" "win32" "pyglet" "tkinter" "pyqt5" "pyqt6" "wxpython" "pygame" "GLUT" "GTK" "Unity" "SDL2_OpenGLES" "SDL2_Direct3D" "SDL2_Software" "Qt5" "Qt6" "DirectX11" "JavaSwing" "Java2D" "GLEW_SDL" "SDL2_OpenGL" "SDL2_OpenGLES2" "psychopy_pyglet")
FULLSCREEN_OPTIONS=("fullscreen" "no_fullscreen")

for framework in $FRAMEWORKS;
do
    for fullscreen_option in $FULLSCREEN_OPTIONS
    do
        FW_PATH="framework_tester_${fullscreen_option}/$framework/${framework}_default"
        case "$framework" in 

            *"psychopy"*)
                cd ./venv
                source Scripts/activate
                python ../$FW_PATH.py &
                PID_framework=$!
                deactivate
                cd ../
                ;;

            *"Java"*)
                java ./$FW_PATH.java &
                PID_framework=$!
                ;;

            *"py"*)
                python ./$FW_PATH.py &
                PID_framework=$! 
                ;;

            *"tkinter"*)
                python ./$FW_PATH.py &
                PID_framework=$! 
                ;;

            *"SDL"*)
                start ./$FW_PATH.exe &
                PID_framework=$! 
                ;;

            *"GLUT"*)
                start ./$FW_PATH.exe &
                PID_framework=$! 
                ;;

            *"GTK"*)
                # set GDK_BACKEND=win32
                # set GDK_BACKEND=OpenGL #????
                start ./$FW_PATH.exe &
                PID_framework=$! 
                ;;

            *"FLTK"*)
                ./$FW_PATH.exe &
                PID_framework=$! 
                ;;

            *"win32"*)
                start ./$FW_PATH.exe &
                PID_framework=$! 
                ;;

            *"Godot"*)
                start ./framework_tester_${fullscreen_option}/GameEngines/${framework}/${framework}_default.exe &
                PID_framework=$!
                ;;

            *"Unity"*)
                start ./framework_tester_${fullscreen_option}/${framework}_default/framework.exe &
                PID_framework=$!
                ;;

            *"DirectX"*)
                cd "./framework_tester_${fullscreen_option}/${framework}_default"
                start "./${framework}_default.exe" &
                PID_framework=$! 
                cd "../../"
                ;;

            *"Qt"*)
                start ./framework_tester_${fullscreen_option}/${framework}_default/${framework}_default.exe &
                PID_framework=$! 
                ;;
        esac

        sleep "5s"

        sigint() {
            kill -INT $PID_framework
        }
        trap sigint INT

        python ./fullscreen_tester.py $framework $fullscreen_option
        PID_FYALMD=$!

        kill -9 $PID_framework
        powershell kill -n "${framework}_${TEST_COMPLEXITY}"
        powershell kill -n "framework"
        powershell kill -n "java"
    done
done




