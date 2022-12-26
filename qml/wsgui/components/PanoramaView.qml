import QtQuick

Item {
    id: root

    property string imageSource
    property int scrollDuration: 60000
    property real maxScrollWidth: image.width
                                  * 5 // 1 center element and 2 for buffer left and right
    readonly property real imageWidth: image.width

    onScrollDurationChanged: d.startScrollingAnimation(false)

    Timer {
        id: scrollingTimer

        interval: 2000
        onTriggered: console.log("triggered")
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

            onFinished: d.startScrollingAnimation(true)
            onRunningChanged: console.log("running: " + running)
            running: false
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

                onStatusChanged: {
                    if (image.status === Image.Ready
                            && !scrollingAnimation.running) {
                        d.startScrollingAnimation(false)
                    }
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
            if (image.status != Image.Ready) {
                return
            }

            recenterContent()

            var duration = root.scrollDuration
            var start = start = d.initialViewBufferWidth + leftBuffer.width
            var end = start + image.width

            if (!fromBeginning && end != start) {
                duration = root.scrollDuration * (1 - (flickable.contentX - start) / (end - start))
                start = flickable.contentX
            }

            scrollingAnimation.duration = duration
            scrollingAnimation.from = start
            scrollingAnimation.to = end

            scrollingAnimation.start()
        }
    }
}
