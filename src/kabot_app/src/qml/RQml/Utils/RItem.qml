import QtQuick 2.12
import QtQml 2.12

import RQml 1.0

Item {
    id: root

    property string topic: "/unnamed"
    property bool isDefaultValue: latestsMessage === defaultMessage

    property var defaultMessage: "N/A"
    property var latestsMessage: defaultMessage

    function sendMessage(msg){
        Ros.sendMessage(root.topic, msg)
    }

    Component.onCompleted: {
       Ros.connectToTopic(root.topic);
    }

    onTopicChanged: {
        Ros.connectToTopic(root.topic);

        if(Ros.mirror[root.topic] !== undefined){
            root.latestsMessage = Ros.mirror[root.topic]
        }
        else{
            root.latestsMessage = root.defaultMessage
        }
    }

    QtObject{
        id: privateMembers
        property var updatedReportsWatcher: Ros.latestMessage[root.topic]
        onUpdatedReportsWatcherChanged: {
            if(Ros.latestMessage[root.topic] !== undefined){
                root.latestsMessage = Ros.latestMessage[root.topic]
            }
        }
    }
}
