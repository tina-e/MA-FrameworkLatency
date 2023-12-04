import numpy as np
from glumpy import app, gloo, gl
from random import random, uniform

WIDTH = int(1920 / 2)
HEIGHT = 1000
WHITE = 1,1,1,1
BLACK = 0,0,0,1
NUM_RECTS = 1000


VERTEX_SHADER = """
         attribute vec2 position;
         attribute vec4 color;
         varying vec4 frag_color;
         void main()
         {
             gl_Position = vec4(position, 0.0, 1.0);
             frag_color = color;
         } """

FRAGMENT_SHADER = """
           varying vec4 frag_color;
           void main() {
               gl_FragColor = frag_color;
           } """


program = gloo.Program(VERTEX_SHADER, FRAGMENT_SHADER, count=(NUM_RECTS*6))
was_clicked = False

def setup_rects():
    global program

    positions = []
    colors = []

    # create random rects
    for i in range(NUM_RECTS-1):
        point_a = uniform(-0.7, 1)
        point_b = uniform(-0.7, 1)

        positions.append((point_a, point_a))
        positions.append((point_a, point_b))
        positions.append((point_b, point_a))
        positions.append((point_b, point_a))
        positions.append((point_a, point_b))
        positions.append((point_b, point_b))

        color1 = random()
        color2 = random()
        color3 = random()
        colors.extend([(color1, color2, color3, 1)] * 6)

    # create white rect top left corner
    positions.append((-1, 1))       # top left
    positions.append((-0.5, 1))     # top right
    positions.append((-1, 0.5))     # bottom left
    positions.append((-1, 0.5))     # bottom left
    positions.append((-0.5, 1))     # top right
    positions.append((-0.5, 0.5))   # bottom right
    colors.extend([WHITE] * 6)

    # set vertices and colors to gloo program
    program['position'] = positions
    program['color'] = colors
        

window = app.Window(width=WIDTH, height=HEIGHT, color=BLACK, fullscreen=False, decoration=False, title="framework", vsync=False)
#window.set_fullscreen(True)
window.set_position(-100, -100)


@window.event
def on_mouse_press(x, y, buttons):
    global was_clicked
    was_clicked = True
    setup_rects()

@window.event
def on_mouse_release(x, y, buttons):
    global was_clicked
    was_clicked = False

@window.event
def on_draw(dt):
    global program
    window.clear()
    if was_clicked:
        program.draw(gl.GL_TRIANGLES)


app.quit()
app.run()
