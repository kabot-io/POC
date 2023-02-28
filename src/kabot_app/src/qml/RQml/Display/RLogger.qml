import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Controls.Material 2.12
import QtQuick.Layouts 1.12

import RQml 1.0
import RQml.Utils 1.0
import RQml.Layout 1.0

RItem{
    id: root
    topic: "/rosout"

    property int debugCount: 0
    property int infoCount: 0
    property int warningCount: 0
    property int errorCount: 0
    property int fatalCount: 0

    function countLogLevel(level){
        switch(level){
            case 10:
                root.debugCount++
                break
            case 20:
                root.infoCount++
                break
            case 30:
                root.warningCount++
                break
            case 40:
                root.errorCount++
                break
            case 50:
                root.fatalCount++
                break
        }
    }

    function discountLogLevel(level){
        switch(level){
            case 10:
                root.debugCount--
                break
            case 20:
                root.infoCount--
                break
            case 30:
                root.warningCount--
                break
            case 40:
                root.errorCount--
                break
            case 50:
                root.fatalCount--
                break
        }
    }

    enum LogLevel{
        Debug   = 10,
        Info    = 20,
        Warning = 30,
        Error   = 40,
        Fatal   = 50
    }

    property int minLogLevel: RLogger.LogLevel.Info

    function clear(){
        root.debugCount = 0
        root.infoCount = 0
        root.warningCount = 0
        root.errorCount = 0
        root.fatalCount = 0
        currentLogsListModel.clear();
    }

    onLatestsMessageChanged: {
        let incomingMsg = Ros.latestMessage[root.topic]
        for(let i = 0; i < currentLogsListModel.count ; i++){
            let currentMsg = currentLogsListModel.get(i)
            if(currentMsg.level === incomingMsg["level"]){
                if(currentMsg.name === incomingMsg["name"]){
                    if(currentMsg.msg === incomingMsg["msg"]){
                        return;
                    }
                }
            }
        }

        if(root.minLogLevel <= Ros.latestMessage[root.topic]["level"]){
            root.countLogLevel(Ros.latestMessage[root.topic]["level"])
            currentLogsListModel.append(Ros.latestMessage[root.topic])
        }
    }

    ListView{
        id: currentLogsView
        anchors.fill: parent
        model:  ListModel{
            id: currentLogsListModel
        }

        header: Rectangle{
            width: currentLogsView.width
            height: currentLogsView.height/10
            color: Material.accent

            RowLayout{
                anchors.fill: parent

                CenteredLabel{
                    text: "Level"
                    Layout.fillHeight: true
                    Layout.preferredWidth: currentLogsView.width/8
                    font.bold: true
                }

                CenteredLabel{
                    text: "Name"
                    Layout.fillHeight: true
                    Layout.preferredWidth: currentLogsView.width/8
                    font.bold: true
                }

                CenteredLabel{
                    text: "Message"
                    Layout.fillHeight: true
                    Layout.fillWidth: true
                    font.bold: true
                }

                Button{
                    text: "Clear all"
                    Layout.fillHeight: true
                    Layout.preferredWidth: currentLogsView.width/8
                    onClicked: {
                        root.clear()
                    }
                }
            }
        }

        delegate: Rectangle{
            width: currentLogsView.width
            height: currentLogsView.height/10
            color: index%2 ? Material.accent : Material.primary

            RowLayout{
                anchors.fill: parent

                CenteredLabel{
                    text: {
                        switch(level){
                        case 10:
                            return "Debug"
                        case 20:
                            return "Info"
                        case 30:
                            return "Warning"
                        case 40:
                            return "Error"
                        case 50:
                            return "Fatal"
                        }
                    }

                    Layout.fillHeight: true
                    Layout.preferredWidth: currentLogsView.width/8
                    font.bold: true
                }

                CenteredLabel{
                    text: name
                    Layout.fillHeight: true
                    Layout.preferredWidth: currentLogsView.width/8
                    font.bold: true
                }

                CenteredLabel{
                    text: msg
                    Layout.fillHeight: true
                    Layout.fillWidth: true
                }

                Button{
                    text: "Delete"
                    Layout.fillHeight: true
                    Layout.preferredWidth: currentLogsView.width/8
                    onClicked: {
                        root.discountLogLevel(level)
                        currentLogsListModel.remove(index)
                    }
                }
            }
        }
    }
}
