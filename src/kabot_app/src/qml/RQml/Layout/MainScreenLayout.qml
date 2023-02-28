import QtQuick 2.12
import QtQuick.Layouts 1.12
import QtQuick.Controls 2.12

import RQml.Utils 1.0

StackView{
    id: root
    property string name: "Template"
    initialItem: CenteredLabel{text: "Template initialItem"}
}
