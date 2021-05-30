import QtQuick 2.0

Rectangle {
    readonly property var noteNames: ["C", "D", "E", "F", "G", "A", "H"];

    id: button;

    width: 40;
    height: 120;
    property alias noteName: buttonText.text;
    property var noteIndex: 0;
    signal noteOn;
    signal noteOff;

    border.color: "#000000"
    gradient: Gradient {
        GradientStop {
            position: 0
            color: "#999999"
        }

        GradientStop {
            position: 1
            color: "#555555"
        }


    }

    TouchPoint {

    }

    Text {
        id: buttonText;
        anchors.left: parent.left;
        anchors.right: parent.right;
        anchors.top: parent.top;
        anchors.topMargin: 5;
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignTop
        font.pointSize: 16;
        color: "#003377";
        text: noteNames[Math.max(0, Math.min(noteNames.length - 1, noteIndex)).toString()];
    }
}
