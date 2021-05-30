import QtQuick 2.12
import QtQuick.Window 2.12

Window {
    width: 1280
    height: 720
    visible: true
    title: qsTr("CuteKeys")

    Row {
        anchors.top: parent.top;
        anchors.bottom: parent.bottom;
        anchors.left: parent.left;
        anchors.right: parent.right;

        spacing: 20;
        NoteButton {
            noteIndex: 0
        }
        NoteButton {
            noteIndex: 1
        }
        NoteButton {
            noteIndex: 2
        }
    }
}
