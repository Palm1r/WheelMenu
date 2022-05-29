import QtQuick

Item {
    id: root

    property var outerItem
    property var outerIndex

    anchors {
        fill: parent
        margins: 20
    }

    Rectangle {
        anchors {
            fill: parent
            margins: 20
        }
        color: outerItem.color
        radius: 4
        border.width: 2
    }

    Text {
        anchors.centerIn: parent
        text: outerIndex
    }
}

