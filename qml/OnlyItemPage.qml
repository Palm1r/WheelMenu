import QtQuick

Item {
    id: root

    property var outerItem
    property var outerIndex

    anchors {
        fill: parent
        margins: 20
    }

    TableButton {
        color: outerItem.color
        text: outerIndex
    }
}

