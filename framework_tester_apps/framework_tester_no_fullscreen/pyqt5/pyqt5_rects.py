#!/usr/bin/python3

from PyQt5 import uic
from PyQt5.QtWidgets import * 
from PyQt5.QtGui import * 
from PyQt5.QtCore import * 
import random
import sys

WIDTH = 1920
HEIGHT = 1080
MIN_X_RECTS = WIDTH / 2
n_rects = 1000
n_horizontal = 10
n_vertical = 10
rect_w = WIDTH / n_horizontal
rect_h = HEIGHT / n_vertical
  
def randint(a, b):
    return a + int((b - a) * random.random())

class MainWindow(QWidget):
    active = False

    def __init__(self):
        super().__init__()
        graphicsView = QGraphicsView()
        graphicsView.setStyleSheet("border: 0px")
        
        self.color = QColor(0, 0, 0)
        self.setGeometry(0, 0, WIDTH, HEIGHT)
        self.setWindowFlags(Qt.FramelessWindowHint)
        self.setWindowTitle('framework')
        self.show()

    def paintEvent(self, event):
        painter = QPainter()
        painter.begin(self)
        brush = QBrush(self.color)
        painter.setBrush(brush)
        painter.drawRect(0, 0, WIDTH, HEIGHT)

        if self.active:
            self.drawRects(painter)
            self.color = QColor(255, 255, 255)
            brush = QBrush(self.color)
            painter.setBrush(brush)
            painter.setPen(Qt.NoPen)
            painter.drawRect(0, 0, 300, 300)

        painter.end()

    def drawRects(self, painter):
        for i in range(n_rects):
            x = randint(MIN_X_RECTS, WIDTH - rect_w)
            y = randint(0, HEIGHT - rect_h)
            r = randint(0, 255)
            g = randint(0, 255)
            b = randint(0, 255)
            t = 255 #randint(0, 255)
            color = QColor(r, g, b, t)
            brush = QBrush(color)
            painter.setBrush(brush)
            painter.setPen(Qt.NoPen)
            painter.drawRect(x, y, int(rect_w), int(rect_h))

    def mousePressEvent(self, event):
        self.active = True
        self.update()

    def mouseReleaseEvent(self, event):
        self.color = QColor(0, 0, 0)
        self.active = False
        self.update()

app = QApplication(sys.argv)
window = MainWindow()
app.exec_()
