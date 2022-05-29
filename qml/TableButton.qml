import QtQuick

Rectangle {
    id: root

    property alias text: buttonText.text
    signal clicked

    anchors {
        fill: parent
        margins: 20
    }
    radius: 4
    opacity: activeArea.pressed ? 0.6 : 1.0
    border.width: 2

    Text {
        id: buttonText

        anchors.centerIn: parent
        text: index
    }

    MouseArea {
        id: activeArea

        anchors.fill: parent
        hoverEnabled: true
        onClicked: root.clicked()
        onHoveredChanged: {
            if (containsMouse)
                root.border.width = 4
            else
                root.border.width = 2
        }
    }
}
