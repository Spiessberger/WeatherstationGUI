import QtQuick

import wsgui.components
import wsgui.data
import wsgui.System
import wsgui.PanomaxImageProvider

Window {
    id: root

    width: 1280
    height: 800
    visible: true
    title: qsTr("Hello World")

    PanoramaView {
        anchors.fill: parent

        imageSource: PanomaxImageProvider.liveImageAvailable ?
                         "image://panomax/" + PanomaxImageProvider.liveImageId : ""
    }

    Column {
        id: dateTimeCol

        property var locale: Qt.locale("de")

        anchors.left: parent.left
        anchors.top: parent.top
        anchors.margins: 10

        spacing: -30

        Text {
            id: time

            text: System.time.toLocaleString(parent.locale, "HH:mm")
            color: "#2C3E50"
            font.pixelSize: 150
            style: Text.Outline
            styleColor: "#A0ECF0F1"
        }
        Text {
            anchors.left: parent.left
            anchors.leftMargin: 5

            width: time.width

            text: System.date.toLocaleString(parent.locale, "ddd dd.MM.yyyy")
            color: "#2C3E50"
            font.pixelSize: 60
            style: Text.Outline
            styleColor: "#A0ECF0F1"
            fontSizeMode: Text.HorizontalFit
        }
    }

    Column {
        anchors.left: parent.left
        anchors.leftMargin: 10
        anchors.verticalCenter: parent.verticalCenter

        spacing: 5

        WeatherDataDisplay {
            weatherDataType: "TEMP_INSIDE"
        }

        WeatherDataDisplay {
            weatherDataType: "HUMIDITY_INSIDE"
        }
    }

    Column {
        anchors.right: parent.right
        anchors.rightMargin: 10
        anchors.verticalCenter: parent.verticalCenter

        spacing: 5

        WeatherDataDisplay {
            weatherDataType: "WIND_SPEED"
        }

        WeatherDataDisplay {
            weatherDataType: "WIND_GUST"
        }

        WeatherDataDisplay {
            weatherDataType: "TEMP_OUTSIDE"
        }

        WeatherDataDisplay {
            weatherDataType: "HUMIDITY_OUTSIDE"
        }
    }
}
