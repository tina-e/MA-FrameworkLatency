import numpy as np
from glumpy import app, gloo, gl
from random import random

WIDTH = 1920
HEIGHT = 1200
WHITE = 1,1,1,1
BLACK = 0,0,0,1

num_rectangles = 1000
positions = []
colors = []

for i in range(num_rectangles):
    random_pos_x = random()
    random_pos_y = random()

    positions.append((random_pos_x, random_pos_x))
    positions.append((random_pos_x, random_pos_y))
    positions.append((random_pos_y, random_pos_x))
    positions.append((random_pos_y, random_pos_x))
    positions.append((random_pos_x, random_pos_y))
    positions.append((random_pos_y, random_pos_y))

    color1 = random()
    color2 = random()
    color3 = random()
    colors.extend([(color1, color2, color3, 1)] * 6)


vertex = """
         attribute vec2 position;
         attribute vec4 color;
         varying vec4 frag_color;
         void main()
         {
             gl_Position = vec4(position, 0.0, 1.0);
             frag_color = color;
         } """

fragment = """
           varying vec4 frag_color;
           void main() {
               gl_FragColor = frag_color;
           } """


window = app.Window(width=WIDTH, height=HEIGHT, color=BLACK, fullscreen=True, decoration=False, title="framework", vsync=False)
window.set_fullscreen(True)

program = gloo.Program(vertex, fragment, count=(num_rectangles*6))
program['position'] = positions
program['color'] = colors


@window.event
def on_draw(dt):
    window.clear()
    program.draw(gl.GL_TRIANGLES)

app.run()
