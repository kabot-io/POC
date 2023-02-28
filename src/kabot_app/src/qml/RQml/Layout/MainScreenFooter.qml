import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12

import RQml 1.0
import RQml.Control 1.0
import RQml.Display 1.0
import RQml.Utils 1.0
import RQml.Layout 1.0

TabBar{
    id: root
    property SwipeView swipeView
    currentIndex: swipeView.currentIndex

    Repeater{
        model: view.count
        delegate: TabButton{
            text: swipeView.itemAt(index).depth === 1 ?
                      swipeView.itemAt(index).name
                    : swipeView.itemAt(index).name + "\n" + swipeView.itemAt(index).currentItem.name
            font.pixelSize: swipeView.itemAt(index).depth === 1 ? 14 : 12
            onPressed: swipeView.itemAt(index).depth === 1 ? "" : swipeView.itemAt(index).pop()
            enabled: !((root.currentIndex != index) && (swipeView.itemAt(root.currentIndex).depth > 1))
        }
    }
}
