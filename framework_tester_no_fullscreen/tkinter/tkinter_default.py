#!/usr/bin/python3
import tkinter as tk

WIDTH = 1920 
HEIGHT = 1080

root = tk.Tk()
root.geometry(f"{WIDTH}x{HEIGHT}+{0}+{0}")
root.overrideredirect(True) #Remove border  
root.title('framework')

canvas = tk.Canvas(root, width=WIDTH, height=HEIGHT, bg="black", borderwidth=0, highlightthickness=0) 
canvas.pack()

def mousePressed(event):
    root.configure(background="white")
    canvas.configure(background="white")
    canvas.create_rectangle(0, 0, WIDTH, HEIGHT, fill="#FFFFFF", outline="")
    
def mouseReleased(event):
    root.configure(background="black")
    canvas.configure(background="black")
    canvas.delete("all")

root.bind("<ButtonPress-1>", mousePressed)
root.bind("<ButtonRelease-1>", mouseReleased)
root.configure(background="black")
#root.pack()

root.mainloop()

