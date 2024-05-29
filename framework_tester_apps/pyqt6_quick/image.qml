import QtQuick 2.15
import QtQuick.Controls 2.15

Rectangle {
    id: root
    width: 1920
    height: 1080
    color: "black"

    Image {
        id: image
        source: "noise.png"
        anchors.centerIn: parent
        visible: false
    }

    MouseArea {
        anchors.fill: parent
        onPressed: root.onMousePress()
        onReleased: root.onMouseRelease()
    }

    function toggleImage() {
        image.visible = !image.visible;
    }

    signal onMousePress
    onOnMousePress: {
        toggleImage();
    }

    signal onMouseRelease
    onOnMouseRelease: {
        toggleImage();
    }
}
