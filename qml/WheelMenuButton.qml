import QtQuick

MouseArea {
    id: root

    property alias buttonIconColor: buttonIcon.color

    property bool activate: false

    Rectangle {
        id: background

        anchors.centerIn: parent
        width: parent.width
        height: width
        radius: width / 2
        opacity: 0.4
    }

    Rectangle {
        id: buttonIcon

        anchors.centerIn: parent
        width: parent.width / 2
        height: width
        radius: 4
        border.width: 2
        border.color: "white"
    }

    states: [
        State {
            when: !activate && !root.containsPress

            PropertyChanges {
                target: background
                visible: false
            }
        },
        State {
            when: activate && !root.containsPress

            PropertyChanges {
                target: background
                visible: true
            }
        },
        State {
            when: root.containsPress

            PropertyChanges {
                target: background
                visible: true
                opacity: 0.2
            }
        }
    ]
}
