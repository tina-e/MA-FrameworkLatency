import os
os.environ['PYGAME_HIDE_SUPPORT_PROMPT'] = "hide"
import pygame

WIDTH = 1920
HEIGHT = 1080
BLACK_BG_COLOR = (0,0,0)

img = pygame.image.load('noise.png')
screen = pygame.display.set_mode((WIDTH, HEIGHT), pygame.FULLSCREEN, vsync=0)
pygame.display.set_caption('framework')
screen.fill(BLACK_BG_COLOR)
pygame.display.flip()


running = True
while running:
    event = pygame.event.poll()
    if event.type == pygame.QUIT:
        running = False
    
    if event.type == pygame.MOUSEBUTTONDOWN:
        screen.blit(img, (0, 0))
    
    if event.type == pygame.MOUSEBUTTONUP:
        screen.fill(BLACK_BG_COLOR)
    
    pygame.display.update()
