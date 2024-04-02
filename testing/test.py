# # # import pygetwindow as gw

# # # for window in gw.getAllWindows():
# # #     print(window)
# # #     if window.title == "framework":
# # #         window.activate()
# # #     elif window.title == "Windows PowerShell":
# # #         window.minimize()

# # import os
# # import shutil

# # from subprocess import Popen, PIPE
# # import threading

# # def move_files_with_prefix(source_folder, destination_folder, prefix):
# #     # Ensure the destination folder exists
# #     if not os.path.exists(destination_folder):
# #         os.makedirs(destination_folder)

# #     # List all files in the source folder
# #     files = os.listdir(source_folder)

# #     # Iterate through the files and move those with content starting with the specified prefix
# #     for file in files:
# #         source_path = os.path.join(source_folder, file)
# #         destination_path = os.path.join(destination_folder, file)

# #         with open(source_path, 'r') as f:
# #             first_line = f.readline().strip()

# #         if first_line.startswith(prefix):
# #             shutil.move(source_path, destination_path)
# #             print(f"Moved {file} to {destination_folder}")

# # # Replace these paths with your actual source and destination folder paths
# # source_folder_path = "./data/sdl_1112_480hz_55"
# # destination_folder_path = "./data/sdl_1112_480hz_55_error"
# # prefix_to_match = "-"

# # #move_files_with_prefix(source_folder_path, destination_folder_path, prefix_to_match)


# # # def init_fw_latency_tester_windup():
# # #         cmd = [f'..\pixel_readers\windup_errorout.exe']
# # #         latency_tester_process = Popen(cmd, stdout=PIPE, bufsize=1, universal_newlines=True)
# # #         print(latency_tester_process)
# # #         for line in latency_tester_process.stdout:
# # #             print(line)
# # #             try:
# # #                 last_fw_latency = int(line)
# # #             except:
# # #                 pass
            
# # #             new_value = True
# # #             #if measuring == False:
# # #             #    break
# # #         latency_tester_process.kill()

# # # init_fw_latency_tester_windup()
# # # import random
# # # for i in range(10):
# # #     print(random.random() * (-1 if random.randint(0, 1) else 1))
# # # import serial
# # # import time

# # # ser = serial.Serial('COM7')  # open serial port
# # # ser.flushInput()

# # # time.sleep(5)

# # # ser.write('c'.encode())

# # # ser_bytes = ser.readline()
# # # print(ser_bytes)
# # # decoded_bytes = ser_bytes.decode("utf-8")
# # # print(decoded_bytes)

# # # time.sleep(2)

# # # for i in range(10):
# # #     ser.write('m'.encode())
# # #     ser_bytes = ser.readline()
# # #     print(ser_bytes)
# # #     decoded_bytes = ser_bytes.decode("utf-8")
# # #     print(decoded_bytes)
# # #     time.sleep(1)


# # # import pygame
# # # import os
# # # os.environ['PYGAME_HIDE_SUPPORT_PROMPT'] = "hide"


# # # (width, height) = (0,0)
# # # running = True
# # # screen = pygame.display.set_mode((width, height), pygame.FULLSCREEN)
# # # pygame.display.set_caption('framework')

# # # background_color_black = (0,0,0)
# # # background_color_white = (255,255,255)

# # # screen.fill(background_color_black)

# # # measure_counter = 0

# # # pygame.display.flip()
# # # clock = pygame.time.Clock()
# # # state = 0
# # # for i in range(8000):
# # #     #clock.tick(500)
# # #     #print(clock.get_fps())
# # #     state = not state
# # #     screen.fill(background_color_black if state else background_color_white)
# # #     pygame.display.update()



# # # import pyttsx3
# # # engine = pyttsx3.init()
# # # engine.setProperty('rate', 130)
# # # engine.say("Hallo Nici! Wie geht es dir heute? Ich piepse jetzt dann 200-mal. Ich hoffe, das stört nicht. Mit freundlichen Füßen!")
# # # engine.runAndWait()

# # import pyautogui
# # pyautogui.moveTo(10, 30)

# from random import random
# import numpy as np
# from glumpy import app, gl, glm, gloo
# from glumpy.geometry import colorcube

# vertex = """
# uniform vec4 ucolor;
# uniform mat4 model;
# uniform mat4 view;
# uniform mat4 projection;
# attribute vec3 position;
# attribute vec4 color;

# varying vec4 v_color;

# void main()
# {
#     v_color = ucolor * color;
#     gl_Position = projection * view * model * vec4(position,1.0);
# }
# """

# fragment = """
# varying vec4 v_color;
# void main()
# {
#     gl_FragColor = v_color;
# }
# """

# window = app.Window(width=1024, height=500, color=(0.30, 0.30, 0.35, 1.00))

# # Define parameters for the second cube
# cube2_position = np.array([1.5, 0, 0])
# cube2_rotation = np.array([0, 45, 0])  # Rotation angles in degrees
# cube2_scale = 1.0

# @window.event
# def on_draw(dt):
#     global theta, phi

#     window.clear()

#     # Draw first cube
#     gl.glDisable(gl.GL_BLEND)
#     gl.glEnable(gl.GL_DEPTH_TEST)
#     gl.glEnable(gl.GL_POLYGON_OFFSET_FILL)
#     cube['ucolor'] = 1, 1, 1, 1
#     cube.draw(gl.GL_TRIANGLES, faces)

#     # Draw second cube
#     model2 = np.eye(4, dtype=np.float32)
#     glm.translate(model2, *cube2_position)
#     glm.rotate(model2, np.radians(theta), 0, 0, 1)
#     glm.rotate(model2, np.radians(phi), 1, 0, 0)
#     glm.scale(model2, cube2_scale)
#     cube['model'] = model2
#     cube.draw(gl.GL_TRIANGLES, faces)

#     # Make cubes rotate
#     theta += 5  # degrees
#     phi += 5  # degrees
#     model = np.eye(4, dtype=np.float32)
#     glm.rotate(model, np.radians(theta), 0, 0, 1)
#     glm.rotate(model, np.radians(phi), 0, 1, 0)
#     cube['model'] = model

# @window.event
# def on_resize(width, height):
#     cube['projection'] = glm.perspective(45.0, width / float(height), 2.0, 100.0)

# @window.event
# def on_init():
#     gl.glEnable(gl.GL_DEPTH_TEST)
#     gl.glPolygonOffset(1, 1)
#     gl.glEnable(gl.GL_LINE_SMOOTH)
#     gl.glLineWidth(0.75)

# vertices, faces, outline = colorcube()
# cube = gloo.Program(vertex, fragment)
# cube.bind(vertices)
# cube['model'] = np.eye(4, dtype=np.float32)
# cube['view'] = glm.translation(0, 0, -5)
# theta, phi = 0, 0

# app.run()

import win32gui
import ctypes
user32 = ctypes.windll.user32


hwnd = win32gui.FindWindow(None, u'framework')
rect = win32gui.GetWindowRect(hwnd)
win32gui.MoveWindow(hwnd, rect[0] - 3, rect[1] - 32, rect[2], rect[3], False)