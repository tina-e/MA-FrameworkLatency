from psychopy import visual, event  # import some libraries from PsychoPy
from psychopy.hardware import mouse
import random


WIDTH = 1920
HEIGHT = 1080
NUM_RECTS = 999
is_clicked = False

mywin = visual.Window([WIDTH, HEIGHT], fullscr=False, units='pix', winType='pyglet')
win_x, win_y = -mywin.size[0] / 2, mywin.size[1] / 2
mywin.color = 'black'


def create_rects():
    rects = []
    for i in range(0, NUM_RECTS):
        r = random.random() * (-1 if random.randint(0, 1) else 1)
        g = random.random() * (-1 if random.randint(0, 1) else 1)
        b = random.random() * (-1 if random.randint(0, 1) else 1)
        x = random.randint(0, WIDTH/2)
        y = random.randint(-HEIGHT/2, HEIGHT/2)
        w = random.randint(1, (WIDTH/2))
        h = random.randint(1, (HEIGHT/2))
        rect = visual.Rect(win=mywin, pos=(x, y), width=w, height=h, fillColor=[r, g, b, 1])
        rects.append(rect)
    rect = visual.Rect(win=mywin, pos=(win_x, win_y), width=600, height=600, fillColor='white')
    rects.append(rect)
    return rects


def update_rects():
    for rect in rects[:len(rects)-1]:
        r = random.random() * (-1 if random.randint(0, 1) else 1)
        g = random.random() * (-1 if random.randint(0, 1) else 1)
        b = random.random() * (-1 if random.randint(0, 1) else 1)
        x = random.randint(0, WIDTH/2)
        y = random.randint(-HEIGHT/2, HEIGHT/2)
        w = random.randint(1, (WIDTH/2))
        h = random.randint(1, (HEIGHT/2))
        rect.pos = (x, y)
        rect.width = w
        rect.height = h
        rect.fillColor = [r, g, b, 1]


mouse = event.Mouse()
rects = create_rects()


while(1):
    if mouse.getPressed()[0] == 1:
        if not is_clicked:
            update_rects()
            is_clicked = True
        for rect in rects:
            rect.draw()
    elif (mouse.getPressed()[0] == 0 and is_clicked):
        is_clicked = False
    #mywin.flip()
    mywin.update()
    
