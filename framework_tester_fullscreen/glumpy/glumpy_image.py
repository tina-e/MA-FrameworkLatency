# based on: https://github.com/glumpy/glumpy/blob/master/examples/gloo-image.py

from glumpy import app, gloo, gl, data


WIDTH = 1920
HEIGHT = 1080
BLACK = 0,0,0,1


vertex = """
    attribute vec2 position;
    attribute vec2 texcoord;
    varying vec2 v_texcoord;
    void main()
    {
        gl_Position = vec4(position, 0.0, 1.0);
        v_texcoord = texcoord;
    }
"""

fragment = """
    uniform sampler2D texture;
    varying vec2 v_texcoord;
    void main()
    {
        gl_FragColor = texture2D(texture, v_texcoord);
    }
"""

window = app.Window(width=WIDTH, height=HEIGHT, color=BLACK, decoration=False, fullscreen=True, title="framework", vsync=False)

program = gloo.Program(vertex, fragment, count=4)
program['position'] = [(-1,-1), (-1,+1), (+1,-1), (+1,+1)]
program['texcoord'] = [( 0, 1), ( 0, 0), ( 1, 1), ( 1, 0)]
program['texture'] = data.get("noise.png")

pressed = False


@window.event
def on_mouse_press(x, y, buttons):
    global pressed
    pressed = True

@window.event
def on_mouse_release(x, y, buttons):
    global pressed
    pressed = False

@window.event
def on_draw(dt):
    window.clear()
    if pressed:
        program.draw(gl.GL_TRIANGLE_STRIP)


app.quit()
app.run()