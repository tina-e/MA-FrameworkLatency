import sys
import signal
from PyQt6.QtWidgets import QApplication
from PyQt6.QtQuick import QQuickView
from PyQt6.QtCore import QUrl

def handle_interrupt(signal, frame):
    QApplication.quit()

if __name__ == "__main__":
    signal.signal(signal.SIGINT, handle_interrupt)
    app = QApplication(sys.argv)
    view = QQuickView()
    view.setSource(QUrl("./framework_tester_apps/pyqt6_quick/image.qml"))
    #view.setGraphicsApi(QQuickView.graphicsApi().Direct3D11)
    #print(view.graphicsApi())
    view.showFullScreen()
    sys.exit(app.exec())
