import numpy as np
from glumpy import app, gloo, gl
from random import random

WIDTH = 1920
HEIGHT = 1200
WHITE = 1,1,1,1
BLACK = (0,0,0,1)

was_clicked = False
program = None

# Number of rectangles
num_rectangles = 8




def setup_rectangles():
    global was_clicked, program
    was_clicked = True

    positions = []
    for i in range(num_rectangles):
        vertex_shader = """
            attribute vec2 position;
            attribute vec2 size;
            attribute vec4 color;
            varying vec4 v_color;
            void main()
            {
                vec2 offset = size * position;
                gl_Position = vec4(offset.x, offset.y, 0.0, 1.0);
                v_color = color;
            }
        """

        fragment_shader = """
            varying vec4 v_color;
            void main()
            {
                gl_FragColor = v_color;
            }
        """

        random_x = random()
        random_y = random()
        position = [[ random_x, random_x],
                    [random_y, random_x], # rechts unten
                    [ random_x, random_y], # links oben
                    [random_y, random_y]]
        positions.append(position)

        sizes = np.random.uniform(1, 1, (num_rectangles, 2))
        colors = np.random.rand(num_rectangles, 4)

        program = gloo.Program(vertex_shader, fragment_shader)
        print(positions)
        program['position'] = positions
        program['size'] = sizes
        program['color'] = colors


#setup_rectangles()
window = app.Window(width=WIDTH, height=HEIGHT, color=BLACK, fullscreen=True, decoration=False, title="framework", vsync=False)
window.set_fullscreen(True)


@window.event
def on_mouse_press(x, y, buttons):
    setup_rectangles()
    
@window.event
def on_mouse_release(x, y, buttons):
    global was_clicked
    was_clicked = False

@window.event
def on_draw(dt):
    global was_clicked, program
    window.clear()
    if was_clicked:
        program.draw(gl.GL_TRIANGLE_STRIP)

app.quit()
app.run()
