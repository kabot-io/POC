import QtQuick 2.12
import RQml 1.0

import RQml.Utils 1.0

ListView{
    anchors.fill: parent
    model: 1
    snapMode: ListView.NoSnap
    delegate: Text{
        height: contentHeight
        width: root.width
        color: "white"
        text: JSON.stringify(Ros.mirror, null, 4)
        wrapMode: Text.WrapAnywhere
    }
}
