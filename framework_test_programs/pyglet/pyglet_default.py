#!/usr/bin/python3

import pyglet
from pyglet.shapes import Rectangle
from pyglet import app
from pyglet.window import Window


# Define the width and height of the window
WINDOW_WIDTH = 1920
WINDOW_HEIGHT = 1200

display = pyglet.canvas.get_display()
screen = display.get_screens()[0]
screen_mode = screen.get_mode()


# Create a Pyglet window
win = Window(width=WINDOW_WIDTH, height=WINDOW_HEIGHT, vsync=False)
win.set_caption('framework')
win.set_fullscreen(fullscreen=True, width=WINDOW_WIDTH, height=WINDOW_HEIGHT, screen=screen, mode=screen_mode)
# win.set_location(0, 0)
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

app.run()
