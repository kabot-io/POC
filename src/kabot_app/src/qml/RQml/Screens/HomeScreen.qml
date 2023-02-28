import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Controls.Material 2.12
import QtQuick.Layouts 1.12

import RQml 1.0
import RQml.Display 1.0
import RQml.Layout 1.0
import RQml.Utils 1.0

MainScreenLayout{
    id: root
    name: "Ariadna strategy center"
    initialItem: GridLayout{
        columns: 3
        rows:3

        Button{
            Layout.fillHeight: true
            Layout.fillWidth: true
            text: "Bulbulator 300%"
        }

        Button{
            Layout.fillHeight: true
            Layout.fillWidth: true
            text: "Akcelerator"
        }

        Button{
            Layout.fillHeight: true
            Layout.fillWidth: true
            text: "Defibrylator"
        }

        Button{
            Layout.fillHeight: true
            Layout.fillWidth: true
            text: "Pull-up"
        }

        Button{
            Layout.fillHeight: true
            Layout.fillWidth: true
            text: "Alert backup register"
        }

        Button{
            Layout.fillHeight: true
            Layout.fillWidth: true
            text: "Error extra handler"
        }
    }
}
