import QtQuick

GridView {
    id: root

    property var outerRowList
    property int innerRowIndex

    signal outerRowIndexChanged(innerRowIndex: int, newOuterRowIndex: int)

    anchors {
        fill: parent
        margins: 20
    }

    model: outerRowList
    cellWidth: (parent.width - 40) / 3
    cellHeight: cellWidth

    delegate: Item {
        width: cellWidth
        height: width

        Rectangle {
            anchors {
                fill: parent
                margins: 20
            }
            color: outerRowList[index].color
            radius: 4
            border.width: 2

            MouseArea {
                anchors.fill: parent
                onClicked: {
                    outerRowIndexChanged(innerRowIndex, index)
                }
            }
        }

        Text {
            anchors.centerIn: parent
            text: index
        }
    }
}

