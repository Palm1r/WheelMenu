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

        TableButton {
            color: outerRowList[index].color
            text: index
            onClicked: outerRowIndexChanged(innerRowIndex, index)
        }
    }
}

