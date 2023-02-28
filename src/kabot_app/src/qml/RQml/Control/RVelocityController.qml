import QtQuick 2.12
import QtQuick.Layouts 1.12
import QtQuick.Controls 2.12
import QtQuick.Controls.Material 2.12

import RQml 1.0
import RQml.Utils 1.0
import RQml.Layout 1.0

RItem{
    id: root

    ColumnLayout{
        anchors.fill: parent
        anchors.margins: 10

        RItem{
            id: velocity
            topic: "/cmd_vel"
        }

        LayoutItem{
            Slider{
                id: linearVelSlider
                anchors.fill: parent
                from: -100
                to: 100
                orientation: Qt.Vertical
                stepSize: 0.5

                onMoved: {
                    velocity.sendMessage({"linear": {"x": linearVelSlider.value}, "angular": {"z": angularVelSlider.value}})
                }

                RowLayout{
                    anchors.fill: parent

                    Item{
                        Layout.fillHeight: parent
                        Layout.fillWidth: parent

                        ColumnLayout{
                            anchors.fill: parent

                            Item {
                                Layout.fillHeight: parent
                                Layout.fillWidth: parent

                                Label{
                                    anchors.centerIn: parent
                                    text: "Linear Velocity m/s"
                                }
                            }

                            Item{
                                Layout.fillHeight: parent
                                Layout.fillWidth: parent

                                Label{
                                    anchors.centerIn: parent
                                    text: velocity.isConnected ? qsTr("%1 m/s").arg(velocity.latestsMessage["linear"]["x"].toFixed(2)) : qsTr("Not Connected")

                                }
                            }

                        }

                    }

                    Item{
                        Layout.fillHeight: parent
                        Layout.fillWidth: parent

                        RowLayout{
                            anchors.fill: parent

                            Item{
                                Layout.fillHeight: parent
                                Layout.fillWidth: parent

                                RVelocityDisplay{
                                    id: linearVelocityDisplay
                                    value: velocity.isConnected ? velocity.latestsMessage["linear"]["x"] : linearVelSlider.value
                                    isLinearVelocity: true
                                    anchors.centerIn: parent
                                    from: linearVelSlider.from
                                    to: linearVelSlider.to
                                    onClicked: linearVelSlider.value = 0
                                }
                            }

                            Item{
                                Layout.fillHeight: parent
                                Layout.fillWidth: parent

                                RVelocityDisplay{
                                    id: angularVelocityDisplay
                                    value: velocity.isConnected ? velocity.latestsMessage["angular"]["z"] : angularVelSlider.value
                                    isLinearVelocity: false
                                    anchors.centerIn: parent
                                    from: angularVelSlider.from
                                    to: angularVelSlider.to
                                    onClicked: angularVelSlider.value = 0
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

                LayoutItem{
                Slider{
                    id: angularVelSlider
                    anchors.fill: parent
                    from: -3
                    to: 3
                    stepSize: 0.1

                    onMoved: {
                        velocity.sendMessage({"angular": {"z": angularVelSlider.value}, "linear": {"x": linearVelSlider.value}})
                    }

                }
                }

                Item {
                    Layout.fillHeight: parent
                    Layout.fillWidth: parent

                    RowLayout{
                        anchors.fill: parent

                        Item{
                            Layout.fillHeight: parent
                            Layout.fillWidth: parent

                            Label{
                                anchors.centerIn: parent
                                text: "Angular Velocity rad/s"
                            }
                        }

                        Item{
                            Layout.fillHeight: parent
                            Layout.fillWidth: parent

                            Label{
                                anchors.centerIn: parent
                                text: velocity.isConnected ? qsTr("%1 rad/s").arg(velocity.latestsMessage["angular"]["z"].toFixed(3)) : qsTr("Not Connected")
                            }
                        }
                    }
                }
            }
        }
    }
}
