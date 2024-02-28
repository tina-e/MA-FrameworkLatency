#!/usr/bin/python3

import pyglet
from pyglet.shapes import Rectangle
from pyglet import app
from pyglet.window import Window
import signal
import sys


# Define the width and height of the window
WINDOW_WIDTH = 1920
WINDOW_HEIGHT = 1080

# display = pyglet.canvas.get_display()
# screen = display.get_screens()[0]
# screen_mode = screen.get_mode()

# Create a Pyglet window
win = Window(width=WINDOW_WIDTH, height=WINDOW_HEIGHT, vsync=False, style='borderless', fullscreen=False)
win.set_location(0, 0)
win.set_caption('framework')
# win.switch_to()
# win.activate()
# print(win.vsync)

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
    sys.exit(0)

signal.signal(signal.SIGTERM, signal_handler)
signal.signal(signal.SIGINT, signal_handler)

app.run()
