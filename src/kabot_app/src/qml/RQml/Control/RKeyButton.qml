import QtQuick 2.12
import QtQuick.Controls 2.12

import RQml 1.0
import RQml.Utils 1.0

RButton {
    id: root
    property var qtKeyValue

    Keys.onPressed: (event) => {
        if(event.key === qtKeyValue){
            root.clicked()
        }
    }
}
