import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Controls.Material 2.12
import QtQuick.Layouts 1.12
import QtQuick.Window 2.12

import RQml 1.0
import RQml.Control 1.0
import RQml.Display 1.0
import RQml.Layout 1.0
import RQml.Screens 1.0
import RQml.Utils 1.0

ApplicationWindow {
    id: window
    title: Style.appTitle
    visible: true
    minimumWidth: 1000
    minimumHeight: 600

    color: Material.background
    header: MainScreenHeader{id: header; contentHeight: window.height/8}
    footer: MainScreenFooter{id: footer; contentHeight: window.height/10; swipeView: view}

    SwipeView{
        id: view
        anchors.fill: parent
        currentIndex: footer.currentIndex

        HomeScreen{}
        ManualControlScreen{}
        SettingsScreen{}
    }
}
