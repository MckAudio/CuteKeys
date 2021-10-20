import QtQuick
import QtQuick.Layouts
import QtQuick.Controls

ColumnLayout {
    spacing: 10

    GridLayout {
        id: controls
        Layout.fillWidth: true;
        columns: 3
        columnSpacing: 5;
        Text {
            Layout.preferredWidth: 80;
            horizontalAlignment: Text.AlignRight;
            text: "Gain:";
        }
        Slider {
            Layout.fillWidth: true;
            id: gainSlider;
            stepSize: 0.1
            to: 0
            from: -60
            value: audio.gain;
            onMoved: audio.gain = value;
        }
        Text {
            id: gainLabel;
            Layout.preferredWidth: 80;
            verticalAlignment: Text.AlignVCenter
            text: audio.gain.toFixed(1) + " dB";
        }

        Text {
            Layout.preferredWidth: 80;
            horizontalAlignment: Text.AlignRight;
            text: "Attack:";
        }
        Slider {
            Layout.fillWidth: true;
            id: attackSlider;
            stepSize: 1
            to: 2000
            from: 0
            value: audio.attack;
            onMoved: audio.attack = value;
        }
        Text {
            id: attackLabel;
            Layout.preferredWidth: 80;
            verticalAlignment: Text.AlignVCenter
            text: audio.attack.toString() + " ms";
        }

        Text {
            Layout.preferredWidth: 80;
            horizontalAlignment: Text.AlignRight;
            text: "Release:";
        }
        Slider {
            Layout.fillWidth: true;
            id: releaseSlider;
            stepSize: 1
            to: 2000
            from: 0
            value: audio.release;
            onMoved: audio.release = value;
        }
        Text {
            id: releaseLabel;
            Layout.preferredWidth: 80;
            verticalAlignment: Text.AlignVCenter
            text: audio.release.toString() + " ms";
        }

        Text {
            Layout.preferredWidth: 80;
            horizontalAlignment: Text.AlignRight;
            text: "Character:";
        }
        Slider {
            Layout.fillWidth: true;
            stepSize: 0.1
            to: 1.0
            from: -1.0
            value: audio.character;
            onMoved: audio.character = value;
        }
        Text {
            Layout.preferredWidth: 80;
            verticalAlignment: Text.AlignVCenter
            text: (Math.round(50.0 * (audio.character + 1.0))).toString() + " %";
        }
    }

    RowLayout {
        Layout.fillHeight: true;
        Layout.fillWidth: true;
        spacing: 15;
        Repeater {
            model: 8
            NoteButton {
                noteIndex: index
                onNoteOn: audio.noteOn
                onNoteOff: audio.noteOff
            }
        }
    }
}
