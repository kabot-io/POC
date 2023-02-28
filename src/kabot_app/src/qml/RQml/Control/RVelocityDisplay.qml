import QtQuick 2.12
import QtQuick.Layouts 1.12
import QtQuick.Controls 2.12
import QtQuick.Controls.Material 2.12

import RQml 1.0
import RQml.Utils 1.0
import RQml.Layout 1.0
import RQml.Control 1.0

Item{
    id: root
    property var value
    property bool isLinearVelocity: true
    property real from: -1
    property real to: 1
    signal clicked

    Rectangle{
        id: rootRectangle
        width: 100
        height: 100
        radius: 100
        color: (area11.pressed || area21.pressed) ?  Material.foreground : Material.accent
        anchors.centerIn: parent

        MouseArea{
            id: area11
            anchors.fill: parent
            onClicked: root.clicked()
        }

        Rectangle{
            id: velocityBoardPlug
            width: rootRectangle.width
            height: root.value > 0 ? rootRectangle.height-(rootRectangle.height*(root.value/root.to)) : rootRectangle.height-(rootRectangle.height*(root.value/root.from))
            color: "transparent"
            anchors.top: rootRectangle.top
            clip: true

            Behavior on height{
                NumberAnimation{
                    easing.type: Easing.OutQuart
                    duration: 500
                }
            }

            Rectangle{
                id:velocityBoardFiller
                anchors.top: parent.top
                radius: rootRectangle.radius
                width: rootRectangle.width
                height: rootRectangle.height
                color: (area11.pressed || area21.pressed) ?  Material.foreground : Material.primary

                MouseArea{
                    id: area21
                    anchors.fill: parent
                    onClicked: root.clicked()
                }
            }
        }
    }

    Label{
        anchors.centerIn: parent
        text: qsTr("%1 m/s").arg(root.value.toFixed(2))
    }
}
