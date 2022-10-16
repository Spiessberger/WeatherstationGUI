import QtQuick

Item {
    id: root

    property string imageSource
    property real contentX
    property real zoomFactor: 1.0
    property real maxScrollWidth: image.width * 5 // 1 center element and 2 for buffer left and right

    Flickable {
        id: flickable

        anchors.fill: parent

        clip: true

        contentX: d.initialViewBufferWidth + leftBuffer.width
        contentWidth: root.maxScrollWidth
        contentHeight: row.height

        onContentXChanged: {
            if (contentX > viewBuffer.width + leftBuffer.width + image.width) {
                console.log("rigth end")
                d.viewBufferWidth += image.width
            } else if (contentX < viewBuffer.width + leftBuffer.width) {
                console.log("left end")
                d.viewBufferWidth -= image.width
            }
        }

        onMovementEnded: d.recenterContent()

        Row {
            id: row

            Item {
                id: viewBuffer

                height: 1
                width: d.viewBufferWidth
            }

            Item {
                id: leftBuffer

                height: image.height
                width: Math.ceil(root.width * 1.2)

                clip: true

                Image {
                    anchors.right: parent.right

                    height: image.height
                    source: image.source
                    fillMode: Image.PreserveAspectFit
                }

                Rectangle {
                    anchors.right: parent.right
                    height: parent.height
                    width: 2
                    color: "red"
                }
            }

            Image {
                id: image
                height: root.height
                source: root.imageSource
                fillMode: Image.PreserveAspectFit

                Rectangle {
                    anchors.right: parent.right
                    height: parent.height
                    width: 2
                    color: "red"
                }
            }

            Item {
                id: rightBuffer

                height: image.height
                width: Math.ceil(root.width * 1.2)

                clip: true

                Image {
                    anchors.left: parent.left

                    height: image.height
                    source: image.source
                    fillMode: Image.PreserveAspectFit
                }
            }
        }
    }

    QtObject {
        id: d

        readonly property int initialViewBufferWidth: flickable.contentWidth / 2
        property real viewBufferWidth: initialViewBufferWidth
        property real contentX: 0

        function recenterContent() {
            console.log("recentering panoramaview...")
            flickable.contentX = flickable.contentX - d.viewBufferWidth + initialViewBufferWidth
            viewBufferWidth = initialViewBufferWidth
        }
    }
}
