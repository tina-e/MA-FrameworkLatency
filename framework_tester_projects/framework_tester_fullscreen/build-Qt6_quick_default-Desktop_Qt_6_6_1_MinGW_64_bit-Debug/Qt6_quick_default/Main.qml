import QtQuick
import QtQuick.Controls

Window {
    width: 640
    height: 480
    visible: true
    title: qsTr("Hello World")

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

