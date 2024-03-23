import pygame
from pygame.locals import *
from random import random, randrange
from OpenGL.GL import *
from OpenGL.GLU import *

vertices = (
    (100, -100, -100),
    (100, 100, -100),
    (-100, 100, -100),
    (-100, -100, -100),
    (100, -100, 100),
    (100, 100, 100),
    (-100, -100, 100),
    (-100, 100, 100)
)

faces = (
    (0, 1, 2, 3),
    (3, 2, 7, 6),
    (6, 7, 5, 4),
    (4, 5, 1, 0),
    (1, 5, 7, 2),
    (4, 0, 3, 6)
)

NUM_CUBES = 166
WIDTH = 1920
HEIGHT = 1080
HALF_WIDTH = int(WIDTH / 2)
HALF_HEIGHT = int(HEIGHT / 2)
X_RECT = -HALF_WIDTH + 300
Y_RECT = -HALF_HEIGHT + 300


colors = [(0, 0, 0)] * NUM_CUBES

position_x = [0] * NUM_CUBES
position_y = [0] * NUM_CUBES
position_z = [0] * NUM_CUBES

rotation_x = [0] * NUM_CUBES
rotation_y = [0] * NUM_CUBES
rotation_z = [0] * NUM_CUBES
rotation_factor = [0] * NUM_CUBES
rotation_factor_temp = [0] * NUM_CUBES

scaling_x = [0] * NUM_CUBES
scaling_y = [0] * NUM_CUBES
scaling_z = [0] * NUM_CUBES


def setupCubes():
    for i in range(NUM_CUBES):
        rotation_factor[i] = random() * 0.1
        rotation_x[i] = random()
        rotation_y[i] = random()
        rotation_z[i] = random()

        colors[i] = (random(), random(), random())

        position_x[i] = randrange(X_RECT, HALF_WIDTH)
        position_y[i] = randrange(-HALF_HEIGHT, HALF_HEIGHT)
        position_z[i] = randrange(100)

        scaling_x[i] = random()
        scaling_y[i] = random()
        scaling_z[i] = random()
    

def drawCube(index):
    rotation_factor_temp[index] += rotation_factor[index]

    glPushMatrix()
    glTranslatef(position_x[index], position_y[index], position_z[index])
    glRotatef(rotation_factor_temp[index], rotation_x[index], rotation_y[index], rotation_z[index])
    glScalef(scaling_x[index], scaling_y[index], scaling_z[index])
    glColor3fv(colors[index])

    glBegin(GL_QUADS)
    for face in faces:
        for vertex in face:
            glVertex3fv(vertices[vertex])
    glEnd()

    glPopMatrix()



pygame.init()
display = (WIDTH, HEIGHT)
pygame.display.set_mode(display, DOUBLEBUF|OPENGL, pygame.FULLSCREEN, vsync=0)
pygame.display.set_caption('framework')

glOrtho(-(WIDTH / 2), WIDTH / 2, HEIGHT / 2, -HEIGHT / 2, -200, 200)
glTranslatef(0.0, 0.0, -1)

was_pressed = False
running = True
while running:
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            running = False
            pygame.quit()
            quit()

        if event.type == pygame.MOUSEBUTTONDOWN:
            was_pressed = True
            setupCubes()
    
        if event.type == pygame.MOUSEBUTTONUP:
            was_pressed = False
    
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT)

    if was_pressed:
        for i in range(NUM_CUBES):
            drawCube(i)
        glColor3f(1, 1, 1)
        glBegin(GL_QUADS)
        glVertex2i(-HALF_WIDTH, -HALF_HEIGHT)
        glVertex2i(X_RECT, -HALF_HEIGHT)
        glVertex2i(X_RECT, Y_RECT)
        glVertex2i(-HALF_WIDTH, Y_RECT)
        glEnd()

    pygame.display.flip()



