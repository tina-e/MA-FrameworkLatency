import numpy as np
from glumpy import app, gloo, gl
from random import random

WIDTH = 1920
HEIGHT = 1200
WHITE = 1,1,1,1
BLACK = 0,0,0,1

# Number of rectangles
num_rectangles = 2

positions = []
colors = []

# Generate random rectangles
for i in range(num_rectangles):
    random_pos_x = random() / 2
    random_pos_y = random() / 2

    positions.append((random_pos_x, random_pos_x))
    positions.append((random_pos_x, random_pos_y))
    positions.append((random_pos_y, random_pos_x))
    positions.append((random_pos_y, random_pos_x))
    positions.append((random_pos_x, random_pos_y))
    positions.append((random_pos_y, random_pos_y))

    color1 = random()
    color2 = random()
    color3 = random()
    colors.append(color1)
    colors.append(color2)
    colors.append(color3)
    colors.append(1)


# Vertex shader code
vertex = """
        attribute vec4  fg_color;
         attribute vec2 position;
         varying vec4  v_fg_color;
         void main()
         {
             gl_Position = vec4(position, 0.0, 1.0);
             v_fg_color = fg_color;
         } """

fragment = """
           uniform vec4 color;
           void main() {
               gl_FragColor = color;
           } """


window = app.Window(width=WIDTH, height=HEIGHT, color=WHITE, fullscreen=True, decoration=False, title="framework", vsync=False)
window.set_fullscreen(True)
# Create glumpy program
program = gloo.Program(vertex, fragment, count=(num_rectangles*6))
program['position'] = positions
#program['size'] = sizes
program['color'] = [(0,1,0,1), (1,0,0,1)]

print(positions)

@window.event
def on_draw(dt):
    window.clear()
    program.draw(gl.GL_TRIANGLES)

app.run()
