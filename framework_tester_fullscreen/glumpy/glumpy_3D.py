from random import random
import numpy as np
from glumpy import app, gl, glm, gloo
from glumpy.geometry import colorcube
import time

WIDTH = 1920
HEIGHT = 1080
NUM_CUBES = 166


RECT_VERTEX = """
attribute vec2 position;
varying vec4 v_color;

void main() {
    gl_Position = vec4(position, 0.0, 1.0);
    v_color = vec4(1.0, 1.0, 1.0, 1.0);
}
"""

RECT_FRAGMENT = """
varying vec4 v_color;

void main() {
    gl_FragColor = v_color;
}
"""


VERTEX = """
uniform vec4 ucolor;
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
attribute vec3 position;

varying vec4 v_color;

void main()
{
    v_color = ucolor;
    gl_Position = projection * view * model * vec4(position, 1.0);
}
"""

FRAGMENT = """
varying vec4 v_color;
void main()
{
    gl_FragColor = v_color;
}
"""

window = app.Window(width=WIDTH, height=HEIGHT, color=(0, 0, 0, 1.00), fullscreen=True, vsync=False, decoration=False, title="framework")

rect_program = gloo.Program(RECT_VERTEX, RECT_FRAGMENT)
rect_program['position'] = np.array([[-1, 1], [-0.5, 1], [-1, 0.5], [-1, 0.5], [-0.5, 1], [-0.5, 0.5]], dtype=np.float32)

vertices, faces, outline = colorcube()
cube_programs = []

x_positions = [0] * NUM_CUBES
y_positions = [0] * NUM_CUBES
z_positions = [0] * NUM_CUBES

x_axis_rotation = [0] * NUM_CUBES 
y_axis_rotation = [0] * NUM_CUBES
z_axis_rotation = [0] * NUM_CUBES

x_axis_rotation_temp = [0] * NUM_CUBES 
y_axis_rotation_temp = [0] * NUM_CUBES
z_axis_rotation_temp = [0] * NUM_CUBES

scales = [0] * NUM_CUBES

show_cubes = False 


def setup_cubes():
    start = time.time()
    for i in range(NUM_CUBES):
        cube = gloo.Program(VERTEX, FRAGMENT)
        cube.bind(vertices)
        cube['model'] = np.eye(4, dtype=np.float32)
        cube['view'] = glm.translation(0, 0, -15)
        cube_programs.append(cube)
    print(time.time() - start) 


def update():
    for i in range(NUM_CUBES):
        cube_programs[i]['ucolor'] = random(), random(), random(), 1        
        x_positions[i] = random() * 5
        y_positions[i] = random() * 5
        z_positions[i] = random() * 5
        x_axis_rotation[i] = random()
        y_axis_rotation[i] = random()
        z_axis_rotation[i] = random()
        scales[i] = random()


@window.event
def on_draw(dt):
    window.clear()
    if show_cubes:
        for i in range(NUM_CUBES):
            x_axis_rotation_temp[i] += x_axis_rotation[i]
            y_axis_rotation_temp[i] += y_axis_rotation[i]
            z_axis_rotation_temp[i] += z_axis_rotation[i]

            model = np.eye(4, dtype=np.float32)
            glm.translate(model, x_positions[i], y_positions[i], z_positions[i])
            glm.scale(model, scales[i])
            glm.rotate(model, x_axis_rotation_temp[i], 1, 0, 0)
            glm.rotate(model, y_axis_rotation_temp[i], 0, 1, 0)
            glm.rotate(model, z_axis_rotation_temp[i], 0, 0, 1)
            cube_programs[i]['model'] = model           
            cube_programs[i].draw(gl.GL_TRIANGLES, faces)
        rect_program.draw(gl.GL_TRIANGLES)


@window.event
def on_resize(width, height):
    for i in range(NUM_CUBES):
        cube_programs[i]['projection'] = glm.perspective(45.0, width / float(height), 2.0, 100.0)
        

@window.event
def on_mouse_press(x, y, button):
    global show_cubes
    show_cubes = True 
    update()


@window.event
def on_mouse_release(x, y, button):
    global show_cubes
    show_cubes = False 


setup_cubes() 
app.run()
