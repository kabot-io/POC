import QtQuick 2.12
import QtQuick.Controls 2.12

import RQml 1.0

Button{
    id: root
    property string topic: "/unnamed"
    property var messageToSend

    Component.onCompleted: {
        Ros.connectToTopic(root.topic);
    }

    onClicked: {
        Ros.sendMessage(root.topic, root.messageToSend)
    }
}
