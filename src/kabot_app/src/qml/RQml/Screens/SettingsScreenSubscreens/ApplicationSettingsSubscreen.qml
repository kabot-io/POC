import QtQuick 2.12
import QtQuick.Layouts 1.12
import QtQuick.Controls 2.12

import RQml 1.0
import RQml.Utils 1.0
import RQml.Control 1.0
import RQml.Display 1.0
import RQml.Layout 1.0

SubscreenLayout{
    name: "Application settings"

    Switch{
        text: "Fullscreen";
        anchors.centerIn: parent;
        onPositionChanged: {
            if(position){
                window.showFullScreen();
            }
            else{
                window.showMaximized();
            }
        }
    }
}

