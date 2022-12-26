import QtQuick

import ws2022.components
import wsgui.System
import wsgui.data
import wsgui.PanomaxImageProvider

Window {
    id: root

    width: 640
    height: 480
    visible: true
    title: qsTr("Hello World")

    PanoramaView {
        anchors.fill: parent

        imageSource: PanomaxImageProvider.liveImageAvailable ?
                         "image://panomax/" + PanomaxImageProvider.liveImageId : ""
    }

    Rectangle {
        anchors.fill: leftCol
        anchors.margins: -5
        color: "#80FFFFFF"
        radius: 4
        border.width: 1
    }

    Column {
        id: leftCol

        anchors.left: parent.left
        anchors.verticalCenter: parent.verticalCenter

        property var locale: Qt.locale()
        Text {
            text: System.time.toLocaleString(parent.locale, "HH:mm:ss")
        }
        Text {
            text: System.date.toLocaleString(parent.locale, "dd.MM.yyyy")
        }

        Text {
            text: tempInside.value ? tempInside.value.toFixed(2) + " " + tempInside.unit : ""

            WeatherData {
                id: tempInside
                type: "TEMP_INSIDE"
            }
        }

        Text {
            text: humInside.value ? humInside.value.toFixed(2) + " " + humInside.unit : ""

            WeatherData {
                id: humInside
                type: "HUMIDITY_INSIDE"
            }
        }
    }

    Rectangle {
        anchors.fill: rightCol
        anchors.margins: -5
        color: "#80FFFFFF"
        radius: 4
        border.width: 1
    }

    Column {
        id: rightCol

        anchors.right: parent.right
        anchors.verticalCenter: parent.verticalCenter

        Text {
            text: tempOutside.value ? tempOutside.value.toFixed(2) + " " + tempOutside.unit : ""

            WeatherData {
                id: tempOutside
                type: "TEMP_OUTSIDE"
            }
        }

        Text {
            text: humOutside.value ? humOutside.value.toFixed(2) + " " + humOutside.unit : ""

            WeatherData {
                id: humOutside
                type: "HUMIDITY_OUTSIDE"
            }
        }
    }
}
