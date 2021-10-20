import QtQuick
import QtQuick.Layouts
import QtQuick.Controls

GridLayout {
    id: dial
    property string name: "control"
    property string unit: "%"
    property real value: 50.0
    property real minimumValue: 0.0
    property real maximumValue: 100.0

    signal dialChanged(real newValue)

    columns: 2
    rows: 2

    Dial {
        Layout.preferredHeight: 75
        Layout.preferredWidth: 75
        Layout.fillWidth: true
        value: dial.value
        Layout.columnSpan: 2
        from: minimumValue
        to: maximumValue
        inputMode: "Vertical"
        onMoved: {
            dialChanged(value)
        }
    }
    Text {
        Layout.fillWidth: true
        horizontalAlignment: Text.AlignRight
        text: dial.name
    }
    Text {
        Layout.fillWidth: true
        horizontalAlignment: Text.AlignLeft
        font.italic: true
        text: dial.value.toFixed(1) + " " + dial.unit

    }
}

/*##^##
Designer {
    D{i:0;autoSize:true;height:480;width:640}
}
##^##*/
