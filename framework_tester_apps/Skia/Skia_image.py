# https://kyamagu.github.io/skia-python/tutorial/canvas.html
import contextlib, glfw, skia
from OpenGL import GL
import random

NUM_RECTS = 999
WIDTH, HEIGHT = 1920, 1080
rect_color = skia.ColorBLACK
isPressed = False
image = None

def randint(a, b):
    return a + int((b - a) * random.random())

@contextlib.contextmanager
def glfw_window():
    if not glfw.init():
        raise RuntimeError('glfw.init() failed')
    glfw.window_hint(glfw.STENCIL_BITS, 8)
    window = glfw.create_window(WIDTH, HEIGHT, 'framework', None, None)
    glfw.make_context_current(window)
    yield window
    glfw.terminate()

@contextlib.contextmanager
def skia_surface(window):
    context = skia.GrDirectContext.MakeGL()
    (fb_width, fb_height) = glfw.get_framebuffer_size(window)
    backend_render_target = skia.GrBackendRenderTarget(
        fb_width,
        fb_height,
        0,  # sampleCnt
        0,  # stencilBits
        skia.GrGLFramebufferInfo(0, GL.GL_RGBA8)
    )
    surface = skia.Surface.MakeFromBackendRenderTarget(
        context, backend_render_target, skia.kBottomLeft_GrSurfaceOrigin,
        skia.kRGBA_8888_ColorType, skia.ColorSpace.MakeSRGB()
    )
    assert surface is not None
    yield surface
    context.abandonContext()


def mouse_button_callback(window, button, action, mods):
    global isPressed, rect_color
    if action == glfw.PRESS:
        isPressed = True
    elif action == glfw.RELEASE:
        isPressed = False
    redraw(window)


def redraw(window):
    GL.glClear(GL.GL_COLOR_BUFFER_BIT)
    with skia_surface(window) as surface:
        with surface as canvas:
            if isPressed:
                canvas.drawImage(image, 0, 0)
            else:
                canvas.drawRect(skia.Rect(0, 0, WIDTH, HEIGHT), skia.Paint(Color=skia.ColorBLACK))
        surface.flushAndSubmit()
        glfw.swap_buffers(window)


with glfw_window() as window:
    GL.glClear(GL.GL_COLOR_BUFFER_BIT)
    glfw.set_mouse_button_callback(window, mouse_button_callback)  

   
    image = skia.Image.open('noise.png')

    monitor = glfw.get_primary_monitor()
    mode = glfw.get_video_mode(monitor)
    glfw.set_window_monitor(window, monitor, 0, 0, mode.size.width, mode.size.height, mode.refresh_rate)
    glfw.swap_interval(0)  # vsync off
    redraw(window)

    while (glfw.get_key(window, glfw.KEY_ESCAPE) != glfw.PRESS
        and not glfw.window_should_close(window)):
        glfw.wait_events()