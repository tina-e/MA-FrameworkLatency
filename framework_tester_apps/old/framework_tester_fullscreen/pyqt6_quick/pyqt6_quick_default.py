import sys
from PyQt6.QtWidgets import QApplication
from PyQt6.QtQuick import QQuickView, QSGRendererInterface
from PyQt6.QtCore import QUrl, QObject, pyqtSlot

class CustomQuickView(QQuickView):
    def __init__(self):
        super().__init__()
        self.setSource(QUrl.fromLocalFile('default.qml'))
        self.rootContext().setContextProperty("app", self)
        self.setGraphicsApi(QQuickView.graphicsApi().Direct3D11)
        print(self.graphicsApi())

    @pyqtSlot()
    def onMousePress(self):
        self.rootObject().setProperty("color", "white")

    @pyqtSlot()
    def onMouseRelease(self):
        self.rootObject().setProperty("color", "black")

if __name__ == "__main__":
    app = QApplication(sys.argv)
    view = CustomQuickView()
    view.showFullScreen()
    sys.exit(app.exec())
