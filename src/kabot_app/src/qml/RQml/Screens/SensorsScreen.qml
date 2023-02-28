import QtQuick 2.12
import QtQuick.Layouts 1.12
import QtQuick.Controls 2.12

import RQml 1.0
import RQml.Utils 1.0
import RQml.Control 1.0
import RQml.Display 1.0
import RQml.Layout 1.0


MainScreenLayout{
    id: root
    name: "Sensors"

    MeshViewer{
        id: meshViewer

        Button{
            id: button
            property bool cameraToggleFlag: false
            onClicked: {
                if(cameraToggleFlag){
                    meshViewer.moveCameraTo(0, 200, -80, 3000)
                    button.cameraToggleFlag = false;
                }
                else{
                    meshViewer.moveCameraTo(0,20, -200, 3000)
                    button.cameraToggleFlag = true;
                }
            }
        }
    }
}
