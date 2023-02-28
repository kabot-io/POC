import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Controls.Material 2.12
import QtQuick.Layouts 1.12

import RQml 1.0
import RQml.Control 1.0
import RQml.Display 1.0
import RQml.Layout 1.0
import RQml.Utils 1.0

ToolBar{
    id: root

    Drawer{
        id: drawer
        width: root.width
        height: window.height - topBar.height
        edge: Qt.TopEdge
        dragMargin: topBar.height

        RLogger{
            id: logger
            anchors.fill: parent
        }
    }

    Rectangle{
        id: topBar
        width: parent.width
        height: parent.height
        y: drawer.position*drawer.height
        color: Material.background

        RowLayout{
            anchors.fill: parent

            LayoutItem{
                CenteredLabel {
                    anchors.fill: parent
                    font.pixelSize: 30
                    text: qsTr("%1 ℹ️  %2 ⚠️\n%3 X  %4 ☠️")
                        .arg(logger.infoCount).arg(logger.warningCount).arg(logger.errorCount).arg(logger.fatalCount)
                }
            }

            LayoutItem{ AppLogo{anchors{fill: parent; margins: 5 }}} //magic number
            LayoutItem{
                RBattery{
                    topic: "/battery"
                    anchors {
                        fill: parent
                        top: parent.top
                        bottom: parent.bottom
                        margins: 5 //magic number
                    }
                    height: parent.heigh
                    width: height*2 //magic number
                }
            }
        }
    }
}
