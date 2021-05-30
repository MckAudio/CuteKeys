import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Layouts 1.3
import QtGraphicalEffects 1.12

Window {
    width: 600
    height: 200
    visible: true
    title: qsTr("CuteKeys")
    color: "#eeeeee"

    //signal noteOn(number idx);
    //signal noteOff(number noteIdx);
    Column {
        anchors.bottom: parent.bottom;
        anchors.left: parent.left;
        anchors.right: parent.right;
        anchors.top: parent.top;

        Text {
            id: header;
            anchors.top: parent.top;
            horizontalAlignment: Text.AlignHCenter
            anchors.left: parent.left;
            anchors.right: parent.right;
            text: object.text
        }

        RowLayout {
            anchors.top: header.bottom;
            anchors.bottom: parent.bottom;
            anchors.left: parent.left;
            anchors.right: parent.right;
            anchors.margins: 10;
            spacing: 15;

            NoteButton {
                id: noteC
                noteIndex: 0
                onNoteOn: {
                    console.log("Note On: " + noteIndex);
                    object.text = "Pressed Key " + noteIndex;
                }
                onNoteOff: {
                    console.log("Note Off: " + noteIndex);
                    object.text = "Released Key " + noteIndex;
                }
            }
            NoteButton {
                id: noteD
                noteIndex: 1
            }
            NoteButton {
                id: noteE
                noteIndex: 2
            }
            NoteButton {
                id: noteF
                noteIndex: 3
            }
            NoteButton {
                id: noteG
                noteIndex: 4
            }
            NoteButton {
                id: noteA
                noteIndex: 5
            }
            NoteButton {
                id: noteH
                noteIndex: 6
            }
        }
    }
}
