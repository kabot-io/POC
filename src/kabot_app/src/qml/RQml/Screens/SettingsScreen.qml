import QtQuick 2.12
import QtQuick.Layouts 1.12
import QtQuick.Controls 2.12

import RQml 1.0
import RQml.Utils 1.0
import RQml.Control 1.0
import RQml.Display 1.0
import RQml.Layout 1.0

import "SettingsScreenSubscreens"

MainScreenLayout{
    id: root
    name: "Settings"

    initialItem: GridLayout{
        columns: 2
        rows: 2

        LayoutItem{
            SubscreenButton{
                anchors.fill: parent
                text: "Ros topics manager"
                mainscreen: root
                subscreen: RosTopicsManagerSubscreen{}
            }
        }
        LayoutItem{
            SubscreenButton{
                anchors.fill: parent
                text: "Application settings"
                mainscreen: root
                subscreen: ApplicationSettingsSubscreen{}
            }
        }
    }
}
