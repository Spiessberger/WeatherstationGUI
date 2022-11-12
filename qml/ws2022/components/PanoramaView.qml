import QtQuick

Item {
    id: root

    property string imageSource
    property int scrollDuration: 60000
    property real zoomFactor: 1.0
    property real maxScrollWidth: image.width * 5 // 1 center element and 2 for buffer left and right
    readonly property real imageWidth: image.width

    onScrollDurationChanged: d.startScrollingAnimation()


    Timer {
        id: scrollingTimer

        interval: 2000
        onTriggered: d.startScrollingAnimation()
    }

    Flickable {
        id: flickable

        anchors.fill: parent

        clip: true

        contentX: d.initialViewBufferWidth + leftBuffer.width
        contentWidth: root.maxScrollWidth
        contentHeight: row.height

        onContentXChanged: {
            if (contentX > viewBuffer.width + leftBuffer.width + image.width) {
                d.viewBufferWidth += image.width
            } else if (contentX < viewBuffer.width + leftBuffer.width) {
                d.viewBufferWidth -= image.width
            }
        }

        onDragStarted: {
            scrollingTimer.stop()
            scrollingAnimation.stop()
        }

        onMovementEnded: {
            d.recenterContent()
            scrollingTimer.start()
        }

        NumberAnimation on contentX {
            id: scrollingAnimation

            onFinished: {
                duration = root.scrollDuration
                from = d.initialViewBufferWidth + leftBuffer.width
                to = scrollingAnimation.from + image.width

                start()
            }
        }

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

        function startScrollingAnimation(fromBeginning) {
            recenterContent()

            if (fromBeginning) {

            }

            var start = d.initialViewBufferWidth + leftBuffer.width
            var end = scrollingAnimation.from + image.width

            var pos = flickable.contentX - start
            var endPos = end - start

            scrollingAnimation.duration = root.scrollDuration * (1 - pos / endPos)
            scrollingAnimation.from = flickable.contentX
            scrollingAnimation.to = start + image.width

            scrollingAnimation.start()
        }
    }
}
