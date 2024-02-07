#!/usr/bin/python3

from PyQt5 import uic
from PyQt5.QtWidgets import * 
from PyQt5.QtGui import * 
from PyQt5.QtCore import * 
import sys
import signal

WIDTH = 1920
HEIGHT = 1200
  
class MainWindow(QWidget):
    def __init__(self):
        super().__init__()

        graphicsView = QGraphicsView()
        graphicsView.setStyleSheet("border: 0px")

        self.setGeometry(0, 0, WIDTH, HEIGHT)
        self.setWindowTitle('framework')
        self.setWindowFlags(Qt.FramelessWindowHint)
        self.color = QColor(0, 0, 0)
        self.show()

    def paintEvent(self, event):
        painter = QPainter()
        painter.begin(self)
        brush = QBrush(self.color)
        pen = QPen(self.color)
        painter.setBrush(brush)
        painter.setPen(pen)
        painter.drawRect(0, 0, WIDTH, HEIGHT)
        painter.end()

    def mousePressEvent(self, event):
        self.color = QColor(255, 255, 255)
        self.update()

    def mouseReleaseEvent(self, event):
        self.color = QColor(0, 0, 0)
        self.update()

app = QApplication(sys.argv)
window = MainWindow()

def signal_handler(signal, frame):
    sys.exit(0)

signal.signal(signal.SIGTERM, signal_handler)
signal.signal(signal.SIGINT, signal_handler)


app.exec_()
