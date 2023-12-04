import numpy as np
from glumpy import app, gl
from glumpy.ext import png

HEIGHT = 1080
WIDTH = 1920
framebuffer = np.zeros((HEIGHT, WIDTH * 3), dtype=np.uint8)

test = gl.glReadPixels(0, 0, 1, 1, gl.GL_RGB, gl.GL_UNSIGNED_BYTE, framebuffer)
print(test)