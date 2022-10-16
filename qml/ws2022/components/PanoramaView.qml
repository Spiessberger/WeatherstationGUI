import QtQuick

Item {
    id: root

    property string imageSource
    property real contentX
    property real zoomFactor

    Flickable {
        id: flickable

        anchors.fill: parent

        contentX: d.initialViewBufferWidth + leftBuffer.width
        contentWidth: image.width * 20
        contentHeight: row.height

        onContentXChanged: {
            if (contentX > viewBuffer.width + leftBuffer.width + image.width) {
                console.log("rigth end")
                d.viewBufferWidth += image.width
            } else if (contentX < viewBuffer.width + leftBuffer.width) {
                console.log("left end")
                d.viewBufferWidth -= image.width
            }
            dani
        }

        Row {
            id: row

            Item {
                id: viewBuffer

                height: root.height
                width: d.viewBufferWidth
            }

            Item {
                id: leftBuffer

                height: image.height
                width: root.width * 1.5

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
                width: root.width * 1.5

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
        readonly property real initialViewBufferWidth: flickable.contentWidth / 2
        property real viewBufferWidth: initialViewBufferWidth
        property real contentX: 0
    }
}
