#!/usr/bin/python3
import tkinter as tk
import random

WIDTH = int(1920 * 0.8)
HEIGHT = int(1200 * 0.8)
MIN_X_RECTS = WIDTH / 2
n_rects = 1000
n_horizontal = 10
n_vertical = 10
rect_w = WIDTH / n_horizontal
rect_h = HEIGHT / n_vertical

def randint(a, b):
    return a + int((b - a) * random.random())

root = tk.Tk()
root.geometry(f"{WIDTH}x{HEIGHT}+{0}+{0}")
root.overrideredirect(True) #Remove border  
root.title('framework')

canvas = tk.Canvas(root, width=WIDTH, height=HEIGHT, bg="black", borderwidth=0, highlightthickness=0)
canvas.pack()


def rgbToHex(r, g, b):
    return "#%02x%02x%02x" % (r, g, b)

def drawNormalRect(color, rect):
    x, y, w, h = rect
    canvas.create_rectangle(x, y, x + w, y + h, fill=color, outline="")

def drawRects():
    for i in range(n_rects):
        x = randint(MIN_X_RECTS, WIDTH - rect_w)
        y = randint(0, HEIGHT - rect_h)
        r = randint(0, 255)
        g = randint(0, 255)
        b = randint(0, 255)
        t = randint(0, 255) # transparency unused, tkinter doesn't support it
        # https://stackoverflow.com/questions/62117203/how-to-make-a-tkinter-canvas-polygon-transparent
        color = rgbToHex(r, g, b)
        drawNormalRect(color, (x, y, int(rect_w), int(rect_h)))
        
    
def mousePressed(event):
    drawRects()
    color = rgbToHex(255, 255, 255)
    drawNormalRect(color, (0, 0, 300, 300))

    
def mouseReleased(event):
    root.configure(background="black")
    canvas.configure(background="black")
    canvas.delete("all")

root.bind("<ButtonPress-1>", mousePressed)
root.bind("<ButtonRelease-1>", mouseReleased)

root.mainloop()

