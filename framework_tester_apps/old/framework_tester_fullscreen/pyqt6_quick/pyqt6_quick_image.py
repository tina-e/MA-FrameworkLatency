import sys
from PyQt6.QtWidgets import QApplication
from PyQt6.QtQuick import QQuickView
from PyQt6.QtCore import QUrl

if __name__ == "__main__":
    app = QApplication(sys.argv)
    view = QQuickView()
    view.setSource(QUrl.fromLocalFile("image.qml"))
    #view.setGraphicsApi(QQuickView.graphicsApi().Direct3D11)
    #print(view.graphicsApi())
    view.showFullScreen()
    sys.exit(app.exec())
