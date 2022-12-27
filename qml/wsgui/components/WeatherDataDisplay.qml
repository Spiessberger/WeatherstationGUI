import QtQuick 2.0

import wsgui.data

Rectangle {
    id: root

    property string weatherDataType
    property alias valueText: value
    property alias unitText: unit

    width: contentItem.width + 20
    height: contentItem.height

    color: "#A0ECF0F1"
    radius: 4
    border.width: 1

    Item {
        id: contentItem

        anchors.centerIn: parent

        width: childrenRect.width
        height: childrenRect.height
        Text {
            id: value

            text: weatherData.value !== undefined ? weatherData.value.toFixed(1) : "-"
            color: "#2C3E50"
            font.pixelSize: 80
        }

        Text {
            id: unit

            anchors.left: value.right
            anchors.leftMargin: 4
            anchors.baseline: value.baseline

            text: weatherData.unit ? weatherData.unit : ""
            color: "#2C3E50"
            font.pixelSize: 40
        }
    }

    WeatherData {
        id: weatherData
        type: root.weatherDataType
    }
}
