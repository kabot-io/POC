import QtGraphicalEffects 1.12
import QtQuick 2.12
import QtQuick.Controls.Material 2.12
import QtQuick.Layouts 1.12

Item{
    id: root

    Image{
        id: logo
        anchors.fill: parent
        fillMode: Image.PreserveAspectFit
        source: "qrc:/images/appLogo.png"
        antialiasing: true

        ColorOverlay {
            anchors.fill: parent
            source: logo
            color: Material.iconColor
        }
    }
}
