import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Controls.Material 2.12
import QtQuick.Layouts 1.12

import RQml 1.0
import RQml.Utils 1.0
import RQml.Layout 1.0

Item{
    id: root

    function refresh(){
        currentTopicsList.clear();
        var jsonObject = Ros.getTopicsInfo();
        for (var key in jsonObject) {
            currentTopicsList.append(jsonObject[key]);
        }
    }

    Component.onCompleted: root.refresh();

    ListView{
        id: topicList
        anchors.fill: parent
        model:  ListModel{
            id: currentTopicsList
        }

        header: Rectangle{
            width: topicList.width
            height: topicList.height/10
            color: Material.accent

            RowLayout{
                anchors.fill: parent

                CenteredLabel{
                    text: "Topic"
                    Layout.fillHeight: true
                    Layout.fillWidth: true
                    font.bold: true
                }

                CenteredLabel{
                    text: "Type"
                    Layout.fillHeight: true
                    Layout.preferredWidth: topicList.width/4
                    font.bold: true
                }

                CenteredLabel{
                    text: "Connected"
                    Layout.fillHeight: true
                    Layout.preferredWidth: topicList.width/8
                    font.bold: true
                }

                Button{
                    text: "Refresh"
                    Layout.fillHeight: true
                    Layout.preferredWidth: topicList.width/8
                    onClicked: {
                        root.refresh();
                    }
                }
            }
        }

        delegate: Rectangle{
            width: topicList.width
            height: topicList.height/10
            color: index%2 ? Material.primary : Material.background

            RowLayout{
                anchors.fill: parent

                CenteredLabel{
                    text: topic
                    Layout.fillHeight: true
                    Layout.fillWidth: true
                    font.bold: true
                }

                CenteredLabel{
                    text: type
                    Layout.fillHeight: true
                    Layout.preferredWidth: topicList.width/4
                    font.bold: true
                }

                CenteredLabel{
                    text: connected
                    Layout.fillHeight: true
                    Layout.preferredWidth: topicList.width/8
                    color: text === "true" ? Material.foreground : "red"
                }

                Button{
                    text: "Connect"
                    Layout.fillHeight: true
                    Layout.preferredWidth: topicList.width/8
                    onClicked: {
                        Ros.connectToTopic(topic)
                        root.refresh()
                    }
                }
            }
        }
    }
}
