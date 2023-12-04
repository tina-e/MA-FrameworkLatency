from PyQt6.QtWidgets import QApplication, QWidget, QGraphicsView, QGraphicsScene
from PyQt6.QtGui import QPainter, QBrush, QPen, QColor
from PyQt6.QtCore import Qt
import sys
import signal

WIDTH = 1920
HEIGHT = 1200
  
class MainWindow(QWidget):
    def __init__(self):
        super().__init__()
        self.graphicsView = QGraphicsView(self)
        self.graphicsView.setStyleSheet("border: 0px")
        self.scene = QGraphicsScene(self.graphicsView)
        self.graphicsView.setScene(self.scene)

        self.showFullScreen()
        self.setWindowTitle('framework')
        self.color = QColor(0, 0, 0)
        self.show()

    def paintEvent(self, event):
        painter = QPainter(self)
        brush = QBrush(self.color)
        pen = QPen(self.color)
        painter.setBrush(brush)
        painter.setPen(pen)
        painter.drawRect(0, 0, WIDTH, HEIGHT)

    def mousePressEvent(self, event):
        self.color = QColor(255, 255, 255)
        self.update()

    def mouseReleaseEvent(self, event):
        self.color = QColor(0, 0, 0)
        self.update()

app = QApplication(sys.argv)
window = MainWindow()

def signal_handler(signum, frame):
    sys.exit(0)

signal.signal(signal.SIGTERM, signal_handler)
signal.signal(signal.SIGINT, signal_handler)

sys.exit(app.exec())
