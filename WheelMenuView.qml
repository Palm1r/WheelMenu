import QtQuick
import QtQuick.Controls

Item {
    id: root

    property bool activate: true//false
    property real scaleProgress: 1
    property alias viewModel: path.model
    property real pathRlength: 2 * Math.PI * pathRadius / 4
    property int menuEdgeSize
    property int menuItemSize: menuEdgeSize / 3

    Behavior on scaleProgress { NumberAnimation {duration: 350}}

    property real pathRadius: width / 2 + itemHeight / 2
    property int itemHeight: width / 2
    property int itemWidth: pathRlength / path.pathItemCount

    signal openFullGridView(var internalModel)
    signal openOneItem()

    height: width
    transform: Scale {
        origin.x: 0
        origin.y: height
        xScale: scaleProgress
        yScale: scaleProgress
    }

    // first line background
    Rectangle {
        anchors {
            horizontalCenter: parent.left
            verticalCenter: parent.bottom
        }
        width: 2 * pathRadius - itemWidth / 2
        height: width
        radius: width / 2
        color: "transparent"
        border.width: itemWidth
        border.color: "lightblue"
    }

    // second line background
    Rectangle {
        anchors {
            horizontalCenter: parent.left
            verticalCenter: parent.bottom
        }
        width: 2 * pathRadius + 50
        height: width
        radius: width / 2
        color: "transparent"
        border.width: 40
        border.color: "lightblue"
    }

    PathView {
        id: path

        anchors.fill: parent
        pathItemCount: 6
        cacheItemCount: 7
        highlightRangeMode: PathView.ApplyRange

        path: Path {
            startX: 0 - menuItemSize / 2
            startY: height - pathRadius

            PathLine {
                x: 0
                y: height - pathRadius
            }

            PathAttribute { name: "itemRotation"; value: 0}
            PathArc {
                x: pathRadius
                y: height
                radiusX: pathRadius
                radiusY: pathRadius
            }
            PathAttribute { name: "itemRotation"; value: 90}
            PathLine {
                x: pathRadius
                y: height + menuItemSize / 2
            }
            PathAttribute { name: "itemRotation"; value: 90}

        }

        delegate: Rectangle {
            id: menuDelegate

            property real itemRotation: PathView.itemRotation

            rotation: PathView.itemRotation
            color: "transparent"
            width: itemWidth
            height: root.itemHeight

            Item {
                id: menubutton
                anchors.bottom: parent.bottom
                width: parent.width
                height: width

                WheelMenuButton {
                    anchors.centerIn: parent
                    width: parent.width / 2
                    height: root.itemHeight
                    buttonIconColor: menuItemColor
                    activate: index === viewModel.lastActiveIndex

                    onClicked: {
                        root.activate = false
                        openFullGridView(menuItemInternalList)
                        viewModel.lastActiveIndex = index
                    }
                }
            }

            Text {
                anchors {
                    bottom: menubutton.top
                    bottomMargin: 35
                    horizontalCenter: parent.horizontalCenter
                }
                text: menuItemName
            }
        }
    }

    states: [
        State {
            when: activate
            PropertyChanges {
                target: root
                scaleProgress: 1.0
            }
        },
        State {
            when: !activate
            PropertyChanges {
                target: root
                scaleProgress: 0.0
            }
        }
    ]
}
