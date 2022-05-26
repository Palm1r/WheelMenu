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
    property real pathRadius: menuEdgeSize

    Behavior on scaleProgress { NumberAnimation {duration: 350}}

    width: parent.width / 2
    height: width
    transform: Scale {
        origin.x: 0
        origin.y: height
        xScale: scaleProgress
        yScale: scaleProgress
    }

    PathView {
        id: path

        anchors.fill: parent
        pathItemCount: 6
        cacheItemCount: 7
        highlightRangeMode: PathView.ApplyRange

        path: Path {
            startX: 0 - menuItemSize / 2
            startY: 0

            PathLine {
                x: 0
                y: 0
            }

            PathAttribute { name: "itemRotation"; value: 0}
            PathArc {
                x: root.width
                y: root.height
                radiusX: pathRadius
                radiusY: pathRadius
            }
            PathAttribute { name: "itemRotation"; value: 90}
            PathLine {
                x: root.width
                y: root.height + menuItemSize / 2
            }
            PathAttribute { name: "itemRotation"; value: 90}

        }

        delegate: Rectangle {
            id: menuDelegate

            property real itemRotation: PathView.itemRotation
            rotation: PathView.itemRotation
            color: "blue"
            width: pathRlength / path.pathItemCount
            height: width / 2

            WheelMenuButton {
                anchors.centerIn: parent
                width: parent.width / 2
                height: width
                buttonIconColor: menuItemColor
            }

            Text {
                anchors.horizontalCenter: parent.horizontalCenter
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
