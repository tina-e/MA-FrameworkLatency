from psychopy import visual, event 
from psychopy.hardware import mouse


WIDTH = 1920
HEIGHT = 1080


mywin = visual.Window([WIDTH, HEIGHT], fullscr=True)
image_stim = visual.ImageStim(mywin, image="../noise.png")
mywin.color = 'black'

mouse = event.Mouse()

is_clicked = False
while(1):
    if (mouse.getPressed()[0] == 1):
        if not is_clicked:
            is_clicked = True
        image_stim.draw()
    elif (mouse.getPressed()[0] == 0 and is_clicked):
        is_clicked = False
        mywin.color = 'black'
    elif 'escape' in event.getKeys():
        break
    #mywin.flip()
    mywin.update()

mywin.close()