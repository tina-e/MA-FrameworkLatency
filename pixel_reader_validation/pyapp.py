#!/usr/bin/python3
import os
os.environ['PYGAME_HIDE_SUPPORT_PROMPT'] = "hide"
import pygame
import sys
import time

(width, height) = (0,0)
running = True
screen = pygame.display.set_mode((width, height), pygame.FULLSCREEN, vsync=0)
pygame.display.set_caption('framework')

background_color_black = (0,0,0)
background_color_white = (255,255,255)

screen.fill(background_color_black)

pygame.display.flip()

num_clicks = 0
while running:
    event = pygame.event.poll()
    if event.type == pygame.QUIT:
        running = False
    
    if event.type == pygame.MOUSEBUTTONDOWN:
        num_clicks = num_clicks + 1
        if num_clicks == 3:
            screen.fill(background_color_white)
            pygame.display.flip()
            start = time.time() * 1000 * 1000
            print(f'start:0:{start}')

            for i in range(1, 255):
                while True:
                    current = time.time() * 1000 * 1000
                    if current - start >= i * 50000:
                        render_start = time.time() * 1000 * 1000
                        screen.fill((i, i, i))
                        pygame.display.flip()
                        render_stop = time.time() * 1000 * 1000
                        print(f'render_start:{i}:{render_start}')
                        print(f'render_stop:{i}:{render_stop}')
                        break  
            running = False 

    pygame.display.update()
