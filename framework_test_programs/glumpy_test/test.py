from glumpy import app, gloo, gl
import pygame

WIDTH = 1920
HEIGHT = 1200
WHITE = 1,1,1,1
BLACK = 0,0,0,0
#PROGRAM = 'osxglut'

#app.use(PROGRAM)

window = app.Window(width=WIDTH, height=HEIGHT, color=BLACK, fullscreen=True)

vertex = """
         attribute vec2 position;
         void main()
         {
             gl_Position = vec4(position, 0.0, 1.0);
         } """

fragment = """
           uniform vec4 color;
           void main() {
               gl_FragColor = color;
           } """

quad = gloo.Program(vertex, fragment, count=4)

quad['position'] = [(-1, -1),
                    (-1, +1),
                    (+1, -1),
                    (+1, +1)]
quad['color'] = BLACK


def handle_events():
    event = pygame.event.poll()
    if event.type == pygame.MOUSEBUTTONDOWN:
        quad['color'] = WHITE
    
    if event.type == pygame.MOUSEBUTTONUP:
        quad['color'] = BLACK
    

@window.event
def on_mouse_press(x, y, button):
    if button == app.window.mouse.LEFT:
        quad['color'] = WHITE

@window.event
def on_mouse_release(x, y, button):
    if button == app.window.mouse.LEFT:
        quad['color'] = BLACK

@window.event
def on_draw(dt):
    window.clear()
    handle_events()
    quad.draw(gl.GL_TRIANGLE_STRIP)

app.run()