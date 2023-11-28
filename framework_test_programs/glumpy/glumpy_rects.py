# import numpy as np
# from glumpy import app, gloo, gl
# from random import random

# WIDTH = 1920
# HEIGHT = 1200
# WHITE = 1,1,1,1
# BLACK = (0,0,0,1)

# was_clicked = False
# program = None

# # Number of rectangles
# num_rectangles = 8

# vertex_shader = """
#     #version 330 core

#     layout(location = 0) in vec2 inPosition; // Input vertex position

#     out vec2 fragPosition; // Output position for the fragment shader
#     out vec3 fragColor;    // Output color for the fragment shader

#     // Function to generate a random float between 0 and 1
#     float random(vec2 seed) {
#         return fract(sin(dot(seed.xy, vec2(12.9898, 78.233))) * 43758.5453);
#     }

#     void main() {
#         // Set the position of the rectangle
#         vec2 position = inPosition;

#         // Set the size of the rectangle
#         vec2 size = vec2(random(position), random(position + vec2(1.0, 0.0)));

#         // Set the color of the rectangle
#         vec3 color = vec3(random(position + vec2(0.0, 1.0)));

#         // Apply the rectangle transformation
#         vec2 transformedPosition = (position / 800.0) * 2.0 - 1.0;
#         vec2 transformedSize = size / 800.0 * 2.0;

#         // Set the final position
#         gl_Position = vec4(transformedPosition + transformedSize, 0.0, 1.0);

#         // Pass data to the fragment shader
#         fragPosition = position;
#         fragColor = color;
#     }
# """

# fragment_shader = """
#     #version 330 core

#     in vec2 fragPosition; // Input position from the vertex shader
#     in vec3 fragColor;    // Input color from the vertex shader

#     out vec4 finalColor;  // Output color of the fragment shader

#     void main() {
#         // Output the color from the vertex shader
#         finalColor = vec4(fragColor, 1.0);
#     }
# """

# #setup_rectangles()
# window = app.Window(width=WIDTH, height=HEIGHT, color=BLACK, fullscreen=True, decoration=False, title="framework", vsync=False)
# window.set_fullscreen(True)

# vertices = np.zeros(1, dtype=[('inPosition', np.float32, 2)])
# vertices['inPosition'] = [(0, 0)]

# vertex_program = gloo.Program(vertex_shader)
# vertex_program.bind(vertices)

# fragment_program = gloo.Program(fragment_shader)







# @window.event
# def on_mouse_press(x, y, buttons):
#     global was_clicked
#     #setup_rectangles()
#     print("press")
#     was_clicked = True
    
# @window.event
# def on_mouse_release(x, y, buttons):
#     global was_clicked
#     was_clicked = False

# @window.event
# def on_draw(dt):
#     global was_clicked, program
#     window.clear()
#     if was_clicked:
#         program.draw(gl.GL_POINTS)

# app.quit()
# app.run()


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
num_rectangles = 4




def setup_rectangles():
    global was_clicked, program
    was_clicked = True

    positions = []
    #for i in range(1000):
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
    program['position'] = positions
    program['size'] = sizes
    program['color'] = colors

        

        


        


setup_rectangles()
window = app.Window(width=WIDTH, height=HEIGHT, color=BLACK, fullscreen=True, decoration=False, title="framework", vsync=False)
window.set_fullscreen(True)


@window.event
def on_mouse_press(x, y, buttons):
    
    print("clicked")
    
@window.event
def on_mouse_release(x, y, buttons):
    global was_clicked
    was_clicked = False
    window.clear()

@window.event
def on_draw(dt):
    global was_clicked, program
    #window.clear()
    #setup_rectangles()
    #if was_clicked:
    try:
        program.draw(gl.GL_TRIANGLES)
    except:
        pass
    

app.quit()
app.run()