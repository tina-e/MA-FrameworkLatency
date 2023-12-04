from glumpy import app, gloo, gl

WIDTH = int(1920 / 2)
HEIGHT = 1000
WHITE = 1,1,1,1
BLACK = 0,0,0,1

VERTEX_SHADER = """
         attribute vec2 position;
         void main()
         {
             gl_Position = vec4(position, 0.0, 1.0);
         } """

FRAGMENT_SHADER = """
           uniform vec4 color;
           void main() {
               gl_FragColor = color;
           } """


window = app.Window(width=WIDTH, height=HEIGHT, color=BLACK, decoration=False, fullscreen=False, title="framework", vsync=False)
#window.set_fullscreen(True)
window.set_position(-100, -100)


program = gloo.Program(VERTEX_SHADER, FRAGMENT_SHADER, count=6)
program['position'] = [(-1, -1),
                        (-1, 1),
                        (1, -1),
                        (1, -1),
                        (-1, 1),
                        (1, 1)]
program['color'] = BLACK


@window.event
def on_mouse_press(x, y, buttons):
    program['color'] = WHITE

@window.event
def on_mouse_release(x, y, buttons):
    program['color'] = BLACK

@window.event
def on_draw(dt):
    window.clear()
    program.draw(gl.GL_TRIANGLES)

app.quit()
app.run()