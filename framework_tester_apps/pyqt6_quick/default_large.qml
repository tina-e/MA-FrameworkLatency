import QtQuick 2.15
import QtQuick.Controls 2.15

Rectangle {
    width: 1920
    height: 1079
    color: "black"

    MouseArea {
        anchors.fill: parent
        onPressed: {
            app.onMousePress()
        }
        onReleased: {
            app.onMouseRelease()
        }
    }
}
