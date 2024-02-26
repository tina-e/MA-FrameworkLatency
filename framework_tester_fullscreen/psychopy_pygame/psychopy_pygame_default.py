from psychopy import visual, event  # import some libraries from PsychoPy
from psychopy.hardware import mouse


WIDTH = 1920
HEIGHT = 1080
is_clicked = False

mywin = visual.Window([WIDTH, HEIGHT], fullscr=True, winType='pygame')
mywin.color = 'black'

mouse = event.Mouse()

while(1):
    if (mouse.getPressed()[0] == 1 and not is_clicked):
        is_clicked = True
        mywin.color = 'white'
    if (mouse.getPressed()[0] == 0 and is_clicked):
        is_clicked = False
        mywin.color = 'black'
    #mywin.flip()
    mywin.update()
    
