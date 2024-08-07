#!/usr/bin/python3
import os
os.environ['PYGAME_HIDE_SUPPORT_PROMPT'] = "hide"
import pygame
import sys
import time

WIDTH = 100
HEIGHT = 100

x, y = 0, 0
os.environ['SDL_VIDEO_WINDOW_POS'] = f'{x},{y}'

running = True
screen = pygame.display.set_mode((WIDTH, HEIGHT), pygame.NOFRAME, vsync=0)
pygame.display.set_caption('framework')

background_color_black = (0,0,0)
background_color_white = (255,255,255)

screen.fill(background_color_black)

measure_counter = 0

pygame.display.flip()

while running:
    event = pygame.event.poll()
    if event.type == pygame.QUIT:
        running = False
    
    if event.type == pygame.MOUSEBUTTONDOWN:
        screen.fill(background_color_white)
    
    if event.type == pygame.MOUSEBUTTONUP:
        screen.fill(background_color_black)
        measure_counter+=1
    
    pygame.display.update()
