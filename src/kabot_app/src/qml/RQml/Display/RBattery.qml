import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Controls.Material 2.12
import QtQuick.Layouts 1.12

import RQml 1.0
import RQml.Utils 1.0
import RQml.Layout 1.0

RItem{
    id: root
    topic: "/unnamed"
    property var batteryChargeLevel: Ros.mirror[root.topic] ? Ros.mirror[root.topic]["batteryChargeLevel"] : 81

    property color batteryStateColor: {
        if(batteryChargeLevel > 80){
            return Material.primaryColor;
        }
        else if(batteryChargeLevel > 40){
            return Material.primaryColor
        }
        else {
            return Material.primaryColor
        }
    }

    Rectangle{
        id: batteryLevelImage
        anchors.fill: parent
        color: Material.background
        border.width: 2
        border.color: Material.primary
        radius: 20

        Rectangle{
            id: betteryFilling
            width: (parent.width-parent.border.width*2)*root.batteryChargeLevel/100
            color: root.batteryStateColor
            radius: 15

            anchors{
                top: parent.top
                bottom: parent.bottom
                margins: parent.border.width
                left: parent.left
            }
        }
    }

    CenteredLabel{
        id: batteryLevelText
        anchors.fill: parent
        text: qsTr("%1%").arg(batteryChargeLevel)
        font.pixelSize: parent.height
        color: Material.primaryTextColor
    }
}
