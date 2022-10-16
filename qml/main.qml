import QtQuick
import ws2022.components

Window {
    width: 640
    height: 480
    visible: true
    title: qsTr("Hello World")

    PanoramaView {
        anchors.fill: parent

        imageSource: "file:C:/Users/Daniel/Downloads/recent_hd.jpg"
    }
}
