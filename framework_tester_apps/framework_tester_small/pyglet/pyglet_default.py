#!/usr/bin/python3

import pyglet
from pyglet.shapes import Rectangle
from pyglet import app
from pyglet.window import Window
import signal
import sys
import os


# Define the width and height of the window
WINDOW_WIDTH = 100
WINDOW_HEIGHT = 100

# Create a Pyglet window
win = Window(width=WINDOW_WIDTH, height=WINDOW_HEIGHT, vsync=False, style='borderless', fullscreen=False)
win.set_location(0, 0)
win.set_caption('framework')

rect = Rectangle(x=0, y=0, width=WINDOW_WIDTH, height=WINDOW_HEIGHT, color=(0, 0, 0))

@win.event
def on_mouse_press(x, y, button, modifiers):
    rect.color = (255, 255, 255)

@win.event
def on_mouse_release(x, y, button, modifiers):
    rect.color = (0, 0, 0)

# Define a function to draw the rectangle
@win.event
def on_draw():
    win.clear()
    rect.draw()

def signal_handler(signal, frame):
    #print('got signal')
    os._exit(0)
    sys.exit(0)

signal.signal(signal.SIGTERM, signal_handler)
signal.signal(signal.SIGINT, signal_handler)

app.run()
