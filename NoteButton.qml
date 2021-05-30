import QtQuick 2.0
import QtQuick.Layouts 1.3
import QtGraphicalEffects 1.12

Rectangle {
    readonly property var noteNames: ["C", "D", "E", "F", "G", "A", "H"];

    id: root;

    Layout.fillWidth: true;
    Layout.fillHeight: true;
    Layout.minimumWidth: 40;
    Layout.minimumHeight: 120;
    color: "#999999"
    radius: 5
    property var noteIndex: 0;
    signal noteOn(int noteIdx);
    signal noteOff(int noteIdx);

    border.color: "#333333"
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
    layer.enabled: true;
    layer.effect: DropShadow {
        color: "#333333"
        transparentBorder: true
        horizontalOffset: 2
        verticalOffset: 3
        radius: 4
        samples: 9
    }

    Rectangle {
        id: shade;
        anchors.fill: parent;
        color: "#000000";
        opacity: 0.0;
        radius: 5;
    }

    MouseArea {
        id: mouseArea;
        anchors.fill: parent;
        onClicked: {
            console.log("Clicked");
        }
        onPressed: {
            console.log("Pressed", noteIndex);
            root.noteOn(noteIndex);
        }
        onReleased: {
            console.log("Released", noteIndex);
            root.noteOff(noteIndex);
        }
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

    states: [
        State {
            name: "pressed"; when: mouseArea.pressed === true
            PropertyChanges {
                target: shade; opacity: 0.4
            }
        },
        State {
            name: "released"; when: mouseArea.released === true
            PropertyChanges {
                target: shade; opacity: 0.0
            }
        }
    ]

    transitions: [
        Transition {
            from: "*"; to: "pressed"
            NumberAnimation { properties: "opacity"; easing.type: Easing.InOutQuad; duration: 80 }
        }, Transition {
            from: "pressed"; to: "*"
            NumberAnimation { properties: "opacity"; easing.type: Easing.InOutQuad; duration: 400 }
        }
    ]
}
