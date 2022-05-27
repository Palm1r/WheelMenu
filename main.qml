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

//    SecondaryPage {
//    }

////    Loader {
////        anchors.fill: parent

////        sourceComponent:
////    }

    WheelMenuView {
        id: menuView

        anchors {
            bottom: parent.bottom
            left: parent.left
        }
        width: parent.width
        viewModel: menuModel
        menuEdgeSize: window.width / 2

        onOpenFullGridView: {
            console.log(internalModel)
        }
    }

    Rectangle {
        id: opacityRamp

        anchors {
            bottom: buttonPanel.top
        }

        width: parent.width
        height: 20
        color: "red"
        opacity: menuView.activate ? 1.0 : 0.0

        Behavior on opacity { NumberAnimation { duration: 150 } }

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
        border.width: menuView.activate ? 0 : 1
        border.color: "gray"

        Row {
            height: parent.height
            leftPadding: 2

            RoundButton {
                id: menuButton

                anchors {
                    verticalCenter: parent.verticalCenter
                }
                height: parent.height - parent.height / 4
                width: height
                background: Rectangle {
                    anchors.fill: parent
                    color: menuView.activate ? "blue" : "gray"
                    radius: width / 2
                }
                onClicked: menuView.activate = !menuView.activate
            }
        }
    }
}
