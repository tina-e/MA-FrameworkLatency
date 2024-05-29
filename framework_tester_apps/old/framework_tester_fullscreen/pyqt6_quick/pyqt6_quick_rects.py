import sys
from PyQt6.QtWidgets import QApplication
from PyQt6.QtQuick import QQuickView
from PyQt6.QtCore import QUrl
from PyQt6.QtGui import QSurfaceFormat

if __name__ == "__main__":
    app = QApplication(sys.argv)

    view = QQuickView()

    # might not work for direct3d
    view.format().setSwapInterval(0)
    view.format().setSwapBehavior(QSurfaceFormat.SwapBehavior.SingleBuffer)
    print(view.format().swapBehavior())
    print(view.format().swapInterval())

    view.setSource(QUrl.fromLocalFile('rects.qml'))
    view.setGraphicsApi(QQuickView.graphicsApi().Direct3D11)
    print(view.graphicsApi())
    view.showFullScreen()

    sys.exit(app.exec())
