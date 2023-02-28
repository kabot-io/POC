import QtQuick 2.12
import QtQuick.Controls 2.12
import QtMultimedia 5.12
import QtWebSockets 1.1

import RQml.Utils 1.0

RItem {
    id: root
    topic: "/depth_camera/image_raw"

    onIsDefaultValueChanged: {
        if(!isDefaultValue){
            socket.url = root.latestsMessage["data"]
            socket.active = true
        }
    }

    WebSocket{
        id: socket
        property string lastMessage
        onTextMessageReceived: lastMessage = message
    }

    Timer{
        interval: 200
        repeat: true
        running: socket.status == WebSocket.Open
        onTriggered: {
            image.source = socket.lastMessage
        }
    }

    CenteredLabel{
        anchors.fill: parent
        text: "No camera image available"
    }

    Image {
        id: image
        anchors.fill: parent
    }

    MediaPlayer {
       id: mediaplayer
       autoPlay: socket.status === WebSocket.Open
    }

    VideoOutput {
       id: output
       anchors.fill: parent
       source: mediaplayer
   }
}
