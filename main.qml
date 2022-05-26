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
        viewModel: menuModel
        menuEdgeSize: window.width / 2
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
