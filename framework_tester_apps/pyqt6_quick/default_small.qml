import QtQuick 2.15
import QtQuick.Controls 2.15

Rectangle {
    width: 100
    height: 100
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
