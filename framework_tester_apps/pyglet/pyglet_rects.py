# based on schmid and wimmer
#!/usr/bin/python3

import pyglet
from pyglet.shapes import Rectangle
from pyglet import app
from pyglet.window import Window
from random import randint

# Define the width and height of the window
WINDOW_WIDTH = 1920
WINDOW_HEIGHT = 1080

n_rects = 999
n_horizontal = 10
n_vertical = 10
rect_w = WINDOW_WIDTH / n_horizontal
rect_h = WINDOW_HEIGHT / n_vertical

# Create a Pyglet window
win = Window(fullscreen=True, vsync=False)

batch = pyglet.graphics.Batch()
bg = Rectangle(x=0, y=0, width=WINDOW_WIDTH, height=WINDOW_HEIGHT, color=(0, 0, 0))
rects = []

def create_rects():
    global rects
    rects = []

    for i in range(n_rects):
        x = randint(300, WINDOW_WIDTH - rect_w)
        y = randint(0, WINDOW_HEIGHT - rect_h)
        r = randint(0, 255)
        g = randint(0, 255)
        b = randint(0, 255)
        color = (r, g, b)
        rects.append(Rectangle(x=x, y=y, width=rect_w, height=rect_h, color=color, batch=batch))

    # white top left rect for sensor
    rects.append(Rectangle(x=0, y=0, width=300, height=WINDOW_HEIGHT, color=(255, 255, 255), batch=batch))

state = 0

@win.event
def on_mouse_press(x, y, button, modifiers):
    global state
    state = 1
    create_rects()

@win.event
def on_mouse_release(x, y, button, modifiers):
    global state
    state = 0
    for r in rects:
        r.delete()

# Define a function to draw the rectangles
@win.event
def on_draw():
    global state, batch
    win.clear()
    if state == 0:
        bg.draw()
    else:
        batch.draw()

app.run()
