import QtQuick
import QtQuick.Layouts
import QtQuick.Controls

GridLayout {
    property string name: "control"
    property string unit: "%"
    property real value: 50.0
    property real minimumValue: 0.0
    property real maximumValue: 100.0

    columns: 2
    rows: 2

    Dial {
        Layout.preferredHeight: 75
        Layout.preferredWidth: 75
        Layout.fillWidth: true
        value: parent.value
        Layout.columnSpan: 2
        from: minimumValue
        to: maximumValue
        onValueChanged: {
            parent.value = value
        }
        inputMode: "Vertical"
    }
    Text {
        Layout.fillWidth: true
        horizontalAlignment: Text.AlignRight
        text: parent.name
    }
    Text {
        Layout.fillWidth: true
        horizontalAlignment: Text.AlignLeft
        font.italic: true
        text: parent.value.toFixed(1) + " " + parent.unit

    }
}

/*##^##
Designer {
    D{i:0;autoSize:true;height:480;width:640}
}
##^##*/
