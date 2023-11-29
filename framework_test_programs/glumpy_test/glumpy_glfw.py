from glumpy import app, gloo, gl

WIDTH = 1920
HEIGHT = 1200
WHITE = 1,1,1,1
BLACK = 0,0,0,1

window = app.Window(width=WIDTH, height=HEIGHT, color=BLACK, fullscreen=True, decoration=False, title="framework", vsync=False)

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


@window.event
def on_mouse_press(x, y, button):
    quad['color'] = WHITE

@window.event
def on_mouse_release(x, y, button):
    quad['color'] = BLACK

@window.event
def on_draw(dt):
    window.clear()
    quad.draw(gl.GL_TRIANGLE_STRIP)

app.quit()
app.run()