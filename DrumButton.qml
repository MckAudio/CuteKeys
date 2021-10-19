import QtQuick
import QtQuick.Layouts
import Qt5Compat.GraphicalEffects

Rectangle {
    id: root;

    Layout.fillWidth: true;
    Layout.fillHeight: true;
    Layout.minimumWidth: 50;
    Layout.minimumHeight: 50;
    color: "#999999"
    radius: 5
    property string title: "";
    property int noteIndex: 0;
    signal noteOn(int noteIdx);
    signal noteOff(int noteIdx);

    border.color: "#333333"
    gradient: Gradient {
        GradientStop {
            position: 0
            color: "#aaaaaa"
        }
        GradientStop {
            position: 0.3
            color: "#999999"
        }
        GradientStop {
            position: 1
            color: "#777777"
        }
    }
    layer.enabled: true;
    layer.effect: DropShadow {
        color: "#333333"
        transparentBorder: true
        horizontalOffset: 2
        verticalOffset: 3
        radius: 4
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
        text: title;
    }

    states: [
        State {
            name: "pressed"; when: mouseArea.pressed
            PropertyChanges {
                target: shade; opacity: 0.4
            }
        },
        State {
            name: "released"; when: mouseArea.released
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

/*##^##
Designer {
    D{i:0;autoSize:true;height:480;width:640}
}
##^##*/
