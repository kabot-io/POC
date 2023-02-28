import QtQuick 2.12
import QtQuick.Layouts 1.12
import QtQuick.Controls 2.12

import RQml 1.0
import RQml.Utils 1.0
import RQml.Control 1.0
import RQml.Display 1.0
import RQml.Layout 1.0

import "ManualControlSubscreens"

MainScreenLayout{
    id: root
    name: "Manual Control"

    initialItem: GridLayout{
        columns: 2
        rows: 2

        LayoutItem{
            SubscreenButton{
                anchors.fill: parent
                text: "Simple controller"
                mainscreen: root
                subscreen: VelocityControllerSubscreen{}
            }
        }
        LayoutItem{
            SubscreenButton{
                anchors.fill: parent
                text: "Advanced Controller"
                mainscreen: root
                subscreen: VelocityControllerWithCameraImageSubscreen{}
            }
        }
    }
}
