import QtQuick
import QtQuick.Layouts
import QtQuick.Controls

ColumnLayout {
    spacing: 10

    onWidthChanged: {
        if (width >= 400) {
            controls.columns = 4
            controls.rows = 1
        } else {
            controls.columns = 2
            controls.rows = 2
        }
    }

    Label {
        Layout.fillWidth: true
        text: drummer.log
        horizontalAlignment: Text.AlignHCenter
    }

    GridLayout {
        id: controls
        Layout.fillWidth: true
        columns: 2
        rows: 2
        columnSpacing: 5
        rowSpacing: 5

        // MOD AMOUNT
        DialControl {
            Layout.preferredWidth: 75
        }
        DialControl {
            Layout.preferredWidth: 75
        }
        DialControl {
            Layout.preferredWidth: 75
        }
        Canvas {
            id: canvas
            Layout.preferredWidth: 120
            Layout.preferredHeight: 90

            onPaint: {
                var ctx = getContext("2d")
                ctx.fillStyle = 'green'
                ctx.strokeStyle = 'black'

                ctx.fillRect(0, 0, width, height)
            }
        }
    }

    GridLayout {
        id: pads
        Layout.fillHeight: true
        Layout.fillWidth: true
        columns: 4
        rows: 2
        columnSpacing: 15
        rowSpacing: 15

        Repeater {
            model: 8
            DrumButton {
                title: `#${index + 1}`
                noteIndex: index
                onNoteOn: {
                    drummer.noteOn(index);
                }
                onNoteOff: {
                    drummer.noteOff(index);
                }
            }
        }
    }
}

/*##^##
Designer {
    D{i:0;autoSize:true;height:480;width:640}
}
##^##*/
