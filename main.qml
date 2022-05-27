import QtQuick
import WheelMenu
import QtQuick.Controls

Window {
    id: window


    width: 720
    height: 900
    visible: true
    title: qsTr("Hello World")

    WheelMenuModel {
        id: menuModel
    }

    WheelMenuView {
        id: menuView

        anchors {
            bottom: parent.bottom
            left: parent.left
        }
        width: parent.width
        viewModel: menuModel
        menuEdgeSize: window.width / 2
    }

    Rectangle {
        id: opacityRamp

        anchors {
            bottom: buttonPanel.top
        }

        width: parent.width
        height: 20
        color: "red"

        gradient: Gradient {
            GradientStop { position: 0.1; color: "transparent"}
            GradientStop { position: 0.9; color: "white" }
        }
    }

    Rectangle {
        id: buttonPanel

        anchors.bottom: parent.bottom
        width: parent.width
        height: 40

        Row {
            height: parent.height

            RoundButton {
                id: menuButton

                height: parent.height
                width: height
                onClicked: menuView.activate = !menuView.activate
            }
        }
    }
}
