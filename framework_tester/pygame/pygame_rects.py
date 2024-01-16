#!/usr/bin/python3
import os
os.environ['PYGAME_HIDE_SUPPORT_PROMPT'] = "hide"
import pygame
import sys
import time
import random

WIDTH = int(1920 * 0.8)
HEIGHT = int(1200 * 0.8)

x, y = 0, 0
os.environ['SDL_VIDEO_WINDOW_POS'] = f'{x},{y}'

running = True
screen = pygame.display.set_mode((WIDTH, HEIGHT), pygame.NOFRAME, vsync=0)
pygame.display.set_caption('framework')

WIDTH = pygame.display.Info().current_w
HEIGHT = pygame.display.Info().current_h
MIN_X_RECTS = WIDTH / 2
n_rects = 1000
n_horizontal = 10
n_vertical = 10
rect_w = WIDTH / n_horizontal
rect_h = HEIGHT / n_vertical

background_color_black = (0,0,0)
background_color_white = (255,255,255)

screen.fill(background_color_black)

measure_counter = 0

pygame.display.flip()

def randint(a, b):
    return a + int((b - a) * random.random())

def drawTransparentRect(surface, color, rect, alpha):
    x, y, w, h = rect
    # Create a new surface with per-pixel alpha.
    image = pygame.Surface((w, h), pygame.SRCALPHA)
    # Fill the image with the color and alpha.
    image.fill((color[0], color[1], color[2], alpha))
    # Blit the image to the surface.
    surface.blit(image, (x, y))

def drawNormalRect(surface, color, rect):
    pygame.draw.rect(surface, color, rect)

def drawRects():
    for i in range(n_rects):
        x = randint(MIN_X_RECTS, WIDTH - rect_w)
        y = randint(0, HEIGHT - rect_h)
        r = randint(0, 255)
        g = randint(0, 255)
        b = randint(0, 255)
        t = 255 #randint(0, 255)
        color = (r, g, b)
        drawTransparentRect(screen, color, (x, y, int(rect_w), int(rect_h)), t)
    
    # white top left rect for sensor
    drawNormalRect(screen, background_color_white, (0, 0, 300, 300))

while running:
    event = pygame.event.poll()
    if event.type == pygame.QUIT:
        running = False
    
    if event.type == pygame.MOUSEBUTTONDOWN:
        drawRects()
    
    if event.type == pygame.MOUSEBUTTONUP:
        screen.fill(background_color_black)
        measure_counter+=1
            
    
    pygame.display.update()
