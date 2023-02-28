import QtQuick 2.12
import QtQuick.Layouts 1.12
import QtQuick.Controls 2.12
import QtQuick.Controls.Material 2.12

import RQml 1.0
import RQml.Display 1.0
import RQml.Layout 1.0
import RQml.Utils 1.0

RItem{
    id: root
    topic: "/cmd_vel"

    RItem{
        id: odom
        topic: "/odom/wheels"
        onLatestsMessageChanged: {
            linearVelDial.value = latestsMessage["twist"]["twist"]["linear"]["x"]
            angularVelDial.value = latestsMessage["twist"]["twist"]["angular"]["z"]
        }
    }

    RowLayout{
        anchors.fill: parent

        LayoutItem{
            ColumnLayout{
                anchors.fill: parent

                FrameWithTitle{
                    title: qsTr("Linear velocity")
                    Layout.fillHeight: true
                    Layout.fillWidth: true

                    Dial{
                        id: linearVelDial
                        anchors.horizontalCenter: parent.horizontalCenter
                        anchors.verticalCenter: parent.verticalCenter
                        from: -50
                        to: 50

                        Label{
                            anchors.centerIn: parent
                            text: qsTr("%1 m/s").arg(linearVelDial.value.toFixed(2))
                        }
                    }
                }

                FrameWithTitle{
                    title: qsTr("Speed multipliers")
                    Layout.fillHeight: true
                    Layout.fillWidth: true

                    RowLayout{
                        anchors.fill: parent
                        anchors.margins: 40

                        LayoutItem{
                            Slider{
                                id: linearVelSlider
                                anchors.fill: parent
                                from: 0
                                to: 30
                                orientation: Qt.Vertical
                                stepSize: 0.5
                            }

                            Label{
                                anchors.fill: parent
                                text: qsTr("%1 m/s").arg(linearVelSlider.value)
                                verticalAlignment: Text.AlignBottom
                            }
                        }

                        LayoutItem{
                            Slider{
                                id: angularVelSlider
                                anchors.fill: parent
                                from: 0
                                to: 8
                                orientation: Qt.Vertical
                                stepSize: 0.2
                            }

                            Label{
                                anchors.fill: parent
                                text: qsTr("%1 rad/s").arg(angularVelSlider.value)
                                verticalAlignment: Text.AlignBottom
                            }
                        }
                    }
                }
            }
        }

        Item{
            Layout.preferredWidth: root.width/2
            Layout.fillHeight: true

            ColumnLayout{
                anchors.fill: parent

                FrameWithTitle{
                    Layout.fillHeight: true
                    Layout.fillWidth: true

                    RCameraImage{
                        anchors.fill: parent
                    }
                }

                Item{
                    Layout.fillWidth: true
                    Layout.preferredHeight: root.height/4

                    RowLayout{
                        anchors.fill: parent
                        Keys.forwardTo: [keyW, keyA, keyS, keyD]

                        LayoutItem{
                            id: arrows

                            GridLayout{
                                anchors.fill: parent
                                rows: 2
                                columns: 3

                                LayoutItem{}
                                RKeyButton{
                                   id: keyW
                                   text: "W"
                                   Layout.fillWidth: true
                                   Layout.fillHeight: true
                                   qtKeyValue: Qt.Key_W
                                   topic: root.topic
                                   messageToSend: {"linear": {"x": linearVelSlider.value}}
                                }
                                LayoutItem{}

                                RKeyButton{
                                   id: keyA
                                   text: "A"
                                   Layout.fillWidth: true
                                   Layout.fillHeight: true
                                   qtKeyValue: Qt.Key_A
                                   topic: root.topic
                                   messageToSend: {"angular": {"z": angularVelSlider.value}}
                                }
                                RKeyButton{
                                   id: keyS
                                   text: "S"
                                   Layout.fillWidth: true
                                   Layout.fillHeight: true
                                   qtKeyValue: Qt.Key_S
                                   topic: root.topic
                                   messageToSend: {"linear": {"x": -linearVelSlider.value}}
                                }
                                RKeyButton{
                                   id: keyD
                                   text: "D"
                                   Layout.fillWidth: true
                                   Layout.fillHeight: true
                                   qtKeyValue: Qt.Key_D
                                   topic: root.topic
                                   messageToSend: {"angular": {"z": -angularVelSlider.value}}
                                }
                            }
                        }
                        LayoutItem{
                            ColumnLayout{
                                anchors.fill: parent

                                RKeyButton{
                                   id: keyBreak
                                   text: "BREAK (SPACE)"
                                   Layout.fillWidth: true
                                   Layout.fillHeight: true
                                   qtKeyValue: Qt.Key_Space
                                   topic: root.topic
                                   messageToSend: {"linear": {"x": 0}, "angular": {"z": 0}}
                                }

                                RKeyButton{
                                   id: keyHorn
                                   text: "HORN (F)"
                                   Layout.fillWidth: true
                                   Layout.fillHeight: true
//                                   qtKeyValue: Qt.Key_F
//                                   topic: root.topic
//                                   messageToSend: {"angular": {"z": angularVelSlider.value}}
                                }
                                RKeyButton{
                                   id: keyTakeMine
                                   text: "TAKE MINE (ENTER)"
                                   Layout.fillWidth: true
                                   Layout.fillHeight: true
//                                   qtKeyValue: Qt.Key_Enter
//                                   topic: root.topic
//                                   messageToSend: {"linear": {"x": -linearVelSlider.value}}
                                }
                            }
                        }
                    }
                }
            }
        }

        LayoutItem{
            ColumnLayout{
                anchors.fill: parent

                FrameWithTitle{
                    Layout.fillHeight: true
                    Layout.fillWidth: true
                    title: "Angular velocity"

                    Dial{
                        id: angularVelDial
                        anchors.horizontalCenter: parent.horizontalCenter
                        anchors.verticalCenter: parent.verticalCenter
                        from: -100
                        to: 100

                        Label{
                            anchors.centerIn: parent
                            text: qsTr("%1 rad/s").arg(angularVelDial.value.toFixed(2))
                        }
                    }
                }

                FrameWithTitle{
                    Layout.fillHeight: true
                    Layout.fillWidth: true
                    clip: true

                    RRosMessagesList{
                        anchors.fill: parent
                    }
                }
            }
        }
    }
}
