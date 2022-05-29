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

    property var gridPageLoader

    signal openFullGridView(outerRowList: var, innerRowIndex: int)
    signal openOneItem(outerItem: var, index: int)

    width: parent.width
    height: width
    visible: scaleProgress !== 0.0

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

            PathAttribute { name: "centerRotation"; value: 0}
            PathLine {
                x: 0
                y: height - pathRadius
            }

            PathAttribute { name: "centerRotation"; value: 0}
            PathArc {
                x: pathRadius
                y: height
                radiusX: pathRadius
                radiusY: pathRadius
            }
            PathAttribute { name: "centerRotation"; value: 90}
            PathLine {
                x: pathRadius
                y: height + menuItemSize / 2
            }
            PathAttribute { name: "centerRotation"; value: 90}
        }

        delegate: Item {
            id: menuDelegate

            property real zeroRotation: 0 - PathView.centerRotation

            rotation: PathView.centerRotation
            width: itemWidth
            height: root.itemHeight

            Connections {
                target: gridPageLoader.item
                function onOuterRowIndexChanged(innerRowIndex, newOuterRowIndex) {
                    if (innerRowIndex === index) {
                        outerRowIndex = newOuterRowIndex;
                        openOneItem(menuItemInternalList[outerRowIndex], outerRowIndex)
                    }
                }
            }

            Item {
                id: menubutton
                anchors.bottom: parent.bottom
                width: parent.width
                height: width

                WheelMenuButton {
                    property int currentIndex

                    anchors.centerIn: parent
                    width: parent.width / 2
                    height: width
                    buttonIconColor: menuItemColor
                    activate: index === viewModel.innerRowIndex
                    rotation: menuDelegate.zeroRotation

                    onClicked: {
                        root.activate = false
                        viewModel.innerRowIndex = index
                        openFullGridView(menuItemInternalList, index)
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

            Rectangle {
                anchors {
                    top: parent.top
                }

                width: parent.width / 2
                height: width
                color: menuItemColor
                radius: 4
                rotation: menuDelegate.zeroRotation
                border.width: 2
                border.color: "black"

                Text {
                    anchors.centerIn: parent
                    text: outerRowIndex
                }

                MouseArea{
                    anchors.fill: parent
                    onClicked: {
                        root.activate = false
                        openOneItem(menuItemInternalList[outerRowIndex], outerRowIndex)
                    }
                }
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
