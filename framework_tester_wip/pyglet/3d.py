import pyglet

from pyglet.gl import glEnable, GL_DEPTH_TEST, GL_CULL_FACE, GL_QUADS
from pyglet.math import Mat4, Vec3


window = pyglet.window.Window(width=720, height=480, resizable=True)
batch = pyglet.graphics.Batch()
time = 0


@window.event
def on_resize(width, height):
    window.viewport = (0, 0, *window.get_framebuffer_size())

    window.projection = Mat4.perspective_projection(window.aspect_ratio, z_near=0.1, z_far=255)
    return pyglet.event.EVENT_HANDLED


@window.event
def on_draw():
    window.clear()
    batch.draw()


def animate(dt):
    global time
    time += dt

    rot_x = Mat4.from_rotation(time, Vec3(1, 0, 0))
    rot_y = Mat4.from_rotation(time/3, Vec3(0, 1, 0))
    rot_z = Mat4.from_rotation(time/2, Vec3(0, 0, 1))
    trans = Mat4.from_translation(Vec3(0, 0, 0))
    model_box.matrix = trans @ rot_x# @ rot_y @ rot_z


if __name__ == "__main__":
    glEnable(GL_DEPTH_TEST)
    glEnable(GL_CULL_FACE)

    x = 0
    y = 0
    z = 1
    X, Y, Z = x+1, y+1, z+1

    tex_coords = ('t2f', (0, 0, 1, 0, 1, 1, 0, 1))

    #model_box = pyglet.resource.model("box.obj", batch=batch)
    batch.add(4, GL_QUADS, None,   ('v3f', (X, y, z,  x, y, z,  x, Y, z,  X, Y, z)), tex_coords) # back
    batch.add(4, GL_QUADS, None,   ('v3f', (x, y, Z,  X, y, Z,  X, Y, Z,  x, Y, Z)), tex_coords) # front
    batch.add(4, GL_QUADS, None,   ('v3f', (x, y, z,  x, y, Z,  x, Y, Z,  x, Y, z)), tex_coords)  # left
    batch.add(4, GL_QUADS, None,   ('v3f', (X, y, Z,  X, y, z,  X, Y, z,  X, Y, Z)), tex_coords)  # right
    batch.add(4, GL_QUADS, None, ('v3f', (x, y, z,  X, y, z,  X, y, Z,  x, y, Z)), tex_coords)  # bottom
    batch.add(4, GL_QUADS, None,    ('v3f', (x, Y, Z,  X, Y, Z,  X, Y, z,  x, Y, z)), tex_coords)  # top

    # Set the application wide view matrix (camera):
    window.view = Mat4.look_at(position=Vec3(0, 0, 5), target=Vec3(0, 0, 0), up=Vec3(0, 1, 0))

    pyglet.clock.schedule_interval(animate, 1 / 60)
    pyglet.app.run()
