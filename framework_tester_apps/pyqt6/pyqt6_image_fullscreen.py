#!/usr/bin/python3

from PyQt6 import uic
from PyQt6.QtWidgets import * 
from PyQt6.QtGui import * 
from PyQt6.QtCore import * 
import sys

WIDTH = 1920
HEIGHT = 1080
  
class MainWindow(QWidget):
    def __init__(self):
        super().__init__()
        graphicsView = QGraphicsView()
        graphicsView.setStyleSheet("border: 0px")

        self.setGeometry(0, 0, WIDTH, HEIGHT)
        self.setWindowTitle('framework')
        #self.setWindowFlags(Qt.X11BypassWindowManagerHint)
        self.color = QColor(0, 0, 0)
        self.img = QPixmap("noise.png")
        self.pressed = False
        self.showFullScreen()
        #self.show()

    def paintEvent(self, event):
        painter = QPainter()
        painter.begin(self)
        if self.pressed:
            painter.drawPixmap(0, 0, self.img)
        else:
            brush = QBrush(self.color)
            pen = QPen(self.color)
            painter.setBrush(brush)
            painter.setPen(pen)
            painter.drawRect(0, 0, WIDTH, HEIGHT)
        painter.end()

    def mousePressEvent(self, event):
        self.pressed = True
        #self.repaint()
        self.update()

    def mouseReleaseEvent(self, event):
        self.pressed = False
        #self.repaint()
        self.update()

app = QApplication(sys.argv)
window = MainWindow()
app.exec()
