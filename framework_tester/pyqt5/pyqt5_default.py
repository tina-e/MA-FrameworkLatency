#!/usr/bin/python3

from PyQt5 import uic
from PyQt5.QtWidgets import * 
from PyQt5.QtGui import * 
from PyQt5.QtCore import * 
import sys
import signal

WIDTH = int(1920 * 0.8)
HEIGHT = int(1200 * 0.8)
  
class MainWindow(QWidget):
    def __init__(self):
        super().__init__()

        #format = QSurfaceFormat()
        #format.setSwapInterval(0)  # 0 for no vsync, 1 for vsync
        #self.setFormat(format)

        graphicsView = QGraphicsView()
        graphicsView.setStyleSheet("border: 0px")

        self.setGeometry(0, 0, WIDTH, HEIGHT)
        self.setWindowTitle('framework')
        self.setWindowFlags(Qt.FramelessWindowHint)
        #self.setWindowFlags(Qt.X11BypassWindowManagerHint)
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
        #self.repaint()
        self.update()

    def mouseReleaseEvent(self, event):
        self.color = QColor(0, 0, 0)
        #self.repaint()
        self.update()

app = QApplication(sys.argv)
window = MainWindow()

def signal_handler(signal, frame):
    sys.exit(0)

signal.signal(signal.SIGTERM, signal_handler)
signal.signal(signal.SIGINT, signal_handler)


app.exec_()
