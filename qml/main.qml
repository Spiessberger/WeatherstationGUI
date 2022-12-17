import QtQuick
import WeatherstationGUI
import wsgui.System

Window {
    width: 640
    height: 480
    visible: true
    title: qsTr("Hello World")

    PanoramaView {
        anchors.fill: parent

        imageSource: PanomaxImageProvider.liveImageId
                     > 0 ? "image://panomax/" + PanomaxImageProvider.liveImageId : ""
    }

    Connections {
        target: PanomaxImageProvider.liveImageDownload

        function onProgressChanged() {
            console.log(PanomaxImageProvider.liveImageDownload.progress)
        }
    }

    Column {
        property var locale: Qt.locale()
        Text {
            text: System.time.toLocaleString(parent.locale, "HH:mm:ss")
        }
        Text {
            text: System.date.toLocaleString(parent.locale, "dd.MM.yyyy")
        }
    }
}
