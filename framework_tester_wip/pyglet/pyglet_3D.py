from pyglet.graphics import shader
from pyglet.gl import *
from pyglet.math import Mat4, Vec3
from random import random, randrange
from pyglet.shapes import Rectangle


WIDTH = 1920
HEIGHT = 1080
NUM_CUBES = 166


VERTEX_SHADER = """
    #version 330
    layout(location = 0) in vec3 vertices;
    layout(location = 1) in vec4 colors;

    out vec4 newColor;
    uniform mat4 view_projection;
    uniform mat4 model;

    void main()
    {
        gl_Position = view_projection * model * vec4(vertices, 1.0f);
        newColor = colors;
    }
"""

FRAGMENT_SHADER = """
    #version 330
    in vec4 newColor;
    out vec4 outColor;

    void main()
    {
        outColor = newColor;
    }
"""

CUBE_VERTICES = [-0.5, -0.5, 0.5,
            0.5, -0.5, 0.5,
            0.5, 0.5, 0.5,
            -0.5, 0.5, 0.5,
            
            -0.5, -0.5, -0.5,
            0.5, -0.5, -0.5,
            0.5, 0.5, -0.5,
            -0.5, 0.5, -0.5]
CUBE_VERTICES = [vertex * 200 for vertex in CUBE_VERTICES]

CUBE_INDICES = [0, 1, 2, 2, 3, 0,
           4, 5, 6, 6, 7, 4,
           4, 5, 1, 1, 0, 4,
           6, 7, 3, 3, 2, 6,
           5, 6, 2, 2, 1, 5,
           7, 4, 0, 0, 3, 7]


window = pyglet.window.Window(width=WIDTH, height=HEIGHT, caption='framework', fullscreen=True, vsync=False)
glEnable(GL_DEPTH_TEST)

state = 0
rect = None
programs = []
batch = pyglet.graphics.Batch()

translation_matrices = []
scaling_matrices = []

rotation_x = rotation_y = rotation_z = []
rotation_factor = []
rotation_factor_temp = [0] * NUM_CUBES


def reset():
    global programs, batch, translation_matrices, scaling_matrices, rotation_x, rotation_y, rotation_z, rotation_factor, rotation_factor_temp
    programs = []
    batch = pyglet.graphics.Batch()
    translation_matrices = []
    scaling_matrices = []
    rotation_x = rotation_y = rotation_z = []
    rotation_factor = []
    rotation_factor_temp = [0] * NUM_CUBES


def init_cubes():
    global rect
    for i in range(NUM_CUBES):
        translation_matrices.append(Mat4.from_translation(Vec3(x=randrange(WIDTH-300)+300, y=randrange(HEIGHT), z=randrange(100))))
        scaling_matrices.append(Mat4.from_scale(Vec3(x=random(), y=random(), z=random())))
                                
        rotation_factor.append(random() * 0.1)
        rotation_x.append(random())
        rotation_y.append(random())
        rotation_z.append(random())

        r = randrange(256)
        g = randrange(256)
        b = randrange(256) 
        colors = (r, g, b, 255, r, g, b, 255, r, g, b, 255, r, g, b, 255, r, g, b, 255,r, g, b, 255,r, g, b, 255,r, g, b, 255)

        vertex_shader = shader.Shader(VERTEX_SHADER, 'vertex')
        fragment_shader = shader.Shader(FRAGMENT_SHADER, 'fragment')
        program = shader.ShaderProgram(vertex_shader, fragment_shader)

        view_matrix = Mat4.from_translation(Vec3(x=0, y=0, z=-200))
        projection_matrix = Mat4.orthogonal_projection(left=0, right=WIDTH, bottom=0, top=HEIGHT, z_near=0.1, z_far=1000)
        view_projection = projection_matrix @ view_matrix
        program['view_projection'] = view_projection

        program.vertex_list_indexed(8, GL_TRIANGLES, batch=batch, indices=CUBE_INDICES, vertices=('f', CUBE_VERTICES), colors=('Bn', colors))
        programs.append(program)
    rect = Rectangle(x=0, y=HEIGHT - 300, width=300, height=300, color=(255, 255, 255))


def draw():
    for i in range(NUM_CUBES):
        rotation_factor_temp[i] += rotation_factor[i]
        rotation_matrix = Mat4.from_rotation(angle=rotation_factor_temp[i], vector=Vec3(x=rotation_x[i], y=rotation_y[i], z=rotation_z[i]))
        model_matrix = translation_matrices[i] @ rotation_matrix @ scaling_matrices[i]
        programs[i]['model'] = model_matrix
    batch.draw()
    rect.draw()
    

@window.event
def on_draw():
    window.clear()
    if state == 1:
        draw()


@window.event
def on_mouse_press(x, y, button, modifiers):
    global state
    state = 1
    init_cubes()
    

@window.event
def on_mouse_release(x, y, button, modifiers):
    global state
    state = 0
    reset()
    

pyglet.app.run()