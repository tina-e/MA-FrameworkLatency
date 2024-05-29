#!/usr/bin/python3
import tkinter as tk
from PIL import Image, ImageTk


WIDTH = 1920 
HEIGHT = 1080


root = tk.Tk()
root.attributes("-fullscreen", True)

canvas = tk.Canvas(root, width=WIDTH, height=HEIGHT, bg="black", borderwidth=0, highlightthickness=0)
canvas.pack()
img = ImageTk.PhotoImage(Image.open("noise.png"))

def mousePressed(event):
    canvas.create_image(0, 0, anchor=tk.NW, image=img)
    
def mouseReleased(event):
    canvas.create_rectangle(0, 0, WIDTH, HEIGHT, fill='black')

root.bind("<ButtonPress-1>", mousePressed)
root.bind("<ButtonRelease-1>", mouseReleased)
root.mainloop()

