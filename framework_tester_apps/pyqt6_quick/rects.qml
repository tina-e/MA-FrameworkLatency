import QtQuick 2.15
import QtQuick.Controls 2.15

Rectangle {
    id: root
    color: "black"
    width: 1920
    height: 1080

    Repeater {
        model: 999

        Rectangle {
            x: 0
            y: 0
            width: 0
            height: 0
            color: "transparent"
            objectName: "rect"
            visible: false
        }
    }

    Rectangle {
        x: 0
        y: 0
        width: 100
        height: 100
        color: "white"
        objectName: "rectWhite"
        visible: false
    }


    MouseArea {
        anchors.fill: parent
        onPressed: root.onMousePress()
        onReleased: root.onMouseRelease()
    }

    function toggleRectangles() {
        for (var i = 0; i < root.children.length; ++i) {
            var item = root.children[i];
            if (item.objectName === "rect") {
                item.color = "#" + Math.floor(Math.random()*16777215).toString(16);
                item.x = Math.random() * (root.width - 100) + 100
                item.y = Math.random() * (root.height - item.height)
                item.width = Math.random() * (root.width - item.x)
                item.height = Math.random() * (root.height - item.y)
                item.visible = !item.visible;
            } else if (item.objectName === "rectWhite") {
                item.visible = !item.visible;
            }
        }
    }

    signal onMousePress
    onOnMousePress: {
        toggleRectangles();
    }

    signal onMouseRelease
    onOnMouseRelease: {
        toggleRectangles();
    }
}
