import sys
import signal
from PyQt6.QtWidgets import QApplication
from PyQt6.QtQuick import QQuickView, QSGRendererInterface
from PyQt6.QtCore import QUrl, QObject, pyqtSlot, Qt

class CustomQuickView(QQuickView):
    def __init__(self):
        super().__init__()
        self.setSource(QUrl('./framework_tester_apps/pyqt6_quick/default.qml'))
        self.rootContext().setContextProperty("app", self)
        self.setPosition(0, 0)
        self.setFlags(Qt.WindowType.FramelessWindowHint | Qt.WindowType.BypassWindowManagerHint)
        # self.setGraphicsApi(QQuickView.graphicsApi().Direct3D11)  # is default

    @pyqtSlot()
    def onMousePress(self):
        self.rootObject().setProperty("color", "white")

    @pyqtSlot()
    def onMouseRelease(self):
        self.rootObject().setProperty("color", "black")

def handle_interrupt(signal, frame):
    QApplication.quit()

if __name__ == "__main__":
    signal.signal(signal.SIGINT, handle_interrupt)
    app = QApplication(sys.argv)
    view = CustomQuickView()
    view.show()
    app.exec()
