#!/usr/bin/python3

from PyQt5 import uic
from PyQt5.QtWidgets import * 
from PyQt5.QtGui import * 
from PyQt5.QtCore import * 
import sys

WIDTH = 1920
HEIGHT = 1200
  
class MainWindow(QWidget):
    def __init__(self):
        super().__init__()
        graphicsView = QGraphicsView()
        graphicsView.setStyleSheet("border: 0px")
        
        self.setGeometry(0, 0, WIDTH, HEIGHT)
        self.setWindowTitle('framework')
        #self.setWindowFlags(Qt.X11BypassWindowManagerHint)
        self.showFullScreen()
        self.color = QColor(0, 0, 0)
        self.show()

    def paintEvent(self, event):
        painter = QPainter()
        painter.begin(self)
        brush = QBrush(self.color)
        painter.setBrush(brush)
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
app.exec_()
