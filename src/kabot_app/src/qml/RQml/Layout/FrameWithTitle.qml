import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Controls.Material 2.12
import QtQuick.Layouts 1.12

Rectangle{
    id: root
    property string title
    color: "transparent"
    border {
        width: 2
        color: Material.primary
    }

    Label{
        anchors.fill: parent
        anchors.topMargin: 16
        text: root.title
        font{
            bold: true
            capitalization: Font.AllUppercase
            pixelSize: 16
        }
        horizontalAlignment: Text.AlignHCenter
    }
}


