#!/usr/bin/python3

from PyQt5 import uic
from PyQt5.QtWidgets import * 
from PyQt5.QtGui import * 
from PyQt5.QtCore import * 
import sys
import signal

WIDTH = int(1920 * 0.8)
HEIGHT = int(1200 * 0.8)
  
class MainWindow(QWindow):
    def __init__(self):
        super().__init__()

        self.graphicsView = QGraphicsView()
        self.graphicsView.setStyleSheet("border: 0px")

        self.setScene(QGraphicsScene(self))

        self.setGeometry(0, 0, WIDTH, HEIGHT)
        self.setTitle('framework')
        self.setFlags(Qt.FramelessWindowHint)

        self.color = QColor(0, 0, 0)
        #self.show()


    def setScene(self, scene):
        self.graphicsView.setScene(scene)
        self.scene = scene


    # def paintEvent(self, event):
    #     painter = QPainter()
    #     painter.begin(self)
    #     brush = QBrush(self.color)
    #     pen = QPen(self.color)
    #     painter.setBrush(brush)
    #     painter.setPen(pen)
    #     painter.drawRect(0, 0, WIDTH, HEIGHT)
    #     painter.end()

    def mousePressEvent(self, event):
        self.color = QColor(255, 255, 255)
        self.renderNow()
        #self.repaint()
        #self.update()

    def mouseReleaseEvent(self, event):
        self.color = QColor(0, 0, 0)
        self.renderNow()
        #self.repaint()
        #self.update()

    def render(self, painter):
        brush = QBrush(self.color)
        pen = QPen(self.color)
        painter.setBrush(brush)
        painter.setPen(pen)
        painter.drawRect(QRect(0, 0, WIDTH, HEIGHT))

    def renderNow(self):
        if not self.isExposed():
            return

        self.graphicsView.render(self.scene, QRectF(0, 0, WIDTH, HEIGHT))
        self.requestUpdate()

app = QApplication(sys.argv)
window = MainWindow()
window.show()

def signal_handler(signal, frame):
    sys.exit(0)

signal.signal(signal.SIGTERM, signal_handler)
signal.signal(signal.SIGINT, signal_handler)


app.exec_()
