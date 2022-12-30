import QtQuick 2.0

Rectangle {
    id: root

    property real direction: 0

    border.color: d.textColor
    border.width: 4
    color: "#A0ECF0F1"
    radius: Math.min(width, height) / 2

    Text {
        anchors.top: root.top
        anchors.horizontalCenter: root.horizontalCenter

        text: "N"
        color: d.textColor
        font.pixelSize: d.fontPixelSize
    }

    Text {
        anchors.right: root.right
        anchors.rightMargin: 5
        anchors.verticalCenter: root.verticalCenter

        text: "O"
        color: d.textColor
        font.pixelSize: d.fontPixelSize
    }

    Text {
        anchors.bottom: root.bottom
        anchors.horizontalCenter: root.horizontalCenter

        text: "S"
        color: d.textColor
        font.pixelSize: d.fontPixelSize
    }

    Text {
        anchors.left: root.left
        anchors.leftMargin: 5
        anchors.verticalCenter: root.verticalCenter

        text: "W"
        color: d.textColor
        font.pixelSize: d.fontPixelSize
    }

    Image {
        anchors.centerIn: parent

        height: root.height / 3

        rotation: root.direction

        source: "qrc:/icons/location-arrow-solid.svg"
        fillMode: Image.PreserveAspectFit

        Behavior on rotation {
            RotationAnimation {
                direction: RotationAnimation.Shortest
                duration: 500
            }
        }
    }

    QtObject {
        id: d

        property int fontPixelSize: 50
        property color textColor: "#2C3E50"
    }
}
