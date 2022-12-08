import QtQuick
import WeatherstationGUI

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
}
