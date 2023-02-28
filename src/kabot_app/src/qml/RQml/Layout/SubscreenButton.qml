import QtQuick 2.12
import QtQuick.Controls 2.12

import RQml.Utils 1.0

Button {
    id: root

    property MainScreenLayout mainscreen
    property SubscreenLayout subscreen: SubscreenLayout{CenteredLabel{anchors.fill: parent; text:"Template subscreen"}}

    onPressed: {
        mainscreen.push(subscreen)
    }
}
