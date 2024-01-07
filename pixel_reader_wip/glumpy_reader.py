from OpenGL.GL import *
from OpenGL.GLUT import *
import numpy as np

width, height = 1, 1

def render_scene():
    glClear(GL_COLOR_BUFFER_BIT)

    glBegin(GL_POINTS)
    glColor3f(1.0, 0.0, 0.0)  # Red color for simplicity
    glVertex2f(0.0, 0.0)
    glEnd()

    glFlush()

def read_pixel_color(x, y):
    glReadBuffer(GL_FRONT)
    data = glReadPixels(x, y, 1, 1, GL_RGB, GL_UNSIGNED_BYTE)
    pixel_color = np.frombuffer(data, dtype=np.uint8)
    pixel_color_normalized = pixel_color / 255.0
    return pixel_color_normalized

def display():
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT)
    # Your OpenGL rendering code here
    glutSwapBuffers()

def main():
    glutInit()  # Initialize GLUT
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH)
    glutCreateWindow(b"OpenGL Window")
    glutDisplayFunc(display)
    glEnable(GL_DEPTH_TEST)
    #glutInitWindowSize(width, height)
    #glutCreateWindow(b'OpenGL Pixel Read')
    #glutDisplayFunc(render_scene)

    # Initialize OpenGL
    #glClearColor(0.0, 0.0, 0.0, 1.0)

    # Read the pixel color
    x, y = 0, 0
    pixel_color = read_pixel_color(x, y)
    print("Pixel color at ({}, {}): {}".format(x, y, pixel_color))

    glutMainLoop()

if __name__ == "__main__":
    main()

# -----------------------------------------------
# try again using python3.8

# import numpy as np
# from glumpy import app, gl, gloo
# from glumpy.gloo import Texture2D

# # Vertex shader
# vertex = """
# attribute vec2 position;
# void main() {
#     gl_Position = vec4(position, 0.0, 1.0);
# }
# """

# # Fragment shader
# fragment = """
# void main() {
#     gl_FragColor = vec4(1.0, 0.0, 0.0, 1.0);  // Red color for simplicity
# }
# """

# # Create a framebuffer object (FBO)
# width, height = 1, 1
# rgb_buf = Texture2D(width=width, height=height)
# depth_buf = gloo.RenderBuffer(shape=(height, width))
# fbo = gloo.FrameBuffer(color=rgb_buf, depth=depth_buf)
# #fbo = gloo.FrameBuffer(color=[texture])

# # Create a shader program
# program = gloo.Program(vertex, fragment)

# # Set up vertex positions
# program['position'] = np.array([[-1, -1], [-1, +1], [+1, -1], [+1, +1]], dtype=np.float32)

# # Function to read pixel color
# def read_pixel_color(x, y):
#     with fbo:
#         gl.glClear(gl.GL_COLOR_BUFFER_BIT)
#         program.draw(gl.GL_TRIANGLE_STRIP)

#     pixel_color = np.frombuffer(fbo.read(components=4, dtype=np.uint8), dtype=np.uint8)
#     pixel_color_normalized = pixel_color[:3] / 255.0
#     return pixel_color_normalized

# # Example usage:
# x, y = 0, 0
# pixel_color = read_pixel_color(x, y)
# print("Pixel color at ({}, {}): {}".format(x, y, pixel_color))

# # Run the application
# app.run()
