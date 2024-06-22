from psychopy import visual, event  
from psychopy.hardware import mouse


WIDTH = 1920
HEIGHT = 1080
is_clicked = False

mywin = visual.Window([WIDTH, HEIGHT], fullscr=True)
mywin.color = 'black'

mouse = event.Mouse()

while(1):
    if (mouse.getPressed()[0] == 1 and not is_clicked):
        is_clicked = True
        mywin.color = 'white'
    elif (mouse.getPressed()[0] == 0 and is_clicked):
        is_clicked = False
        mywin.color = 'black'
    elif 'escape' in event.getKeys():
        break
    #mywin.flip()
    mywin.update()
    
mywin.close()