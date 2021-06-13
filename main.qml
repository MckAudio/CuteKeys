import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Layouts 1.3
import QtGraphicalEffects 1.12
import QtQuick.Controls 2.12

Window {
    width: 600
    height: 350
    visible: true
    title: qsTr("CuteKeys")
    color: "#eeeeee"

    //signal noteOn(number idx);
    //signal noteOff(number noteIdx);
    ColumnLayout {
        anchors.bottom: parent.bottom;
        spacing: 10
        anchors.left: parent.left;
        anchors.right: parent.right;
        anchors.top: parent.top;
        anchors.margins: 10;

        GridLayout {
            id: controls
            Layout.fillWidth: true;
            columns: 3;
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
                onValueChanged: audio.gain = value;
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
                onValueChanged: audio.attack = value;
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
                onValueChanged: audio.release = value;
            }
            Text {
                id: releaseLabel;
                Layout.preferredWidth: 80;
                verticalAlignment: Text.AlignVCenter
                text: audio.release.toString() + " ms";
            }
        }

        RowLayout {
            /*
            anchors.left: parent.left;
            anchors.right: parent.right;
            anchors.top: controls.bottom;
            anchors.bottom: parent.bottom;
            */
            Layout.fillHeight: true;
            Layout.fillWidth: true;
            spacing: 15;

            NoteButton {
                id: noteC
                noteIndex: 0
                onNoteOn: {
                    audio.noteOn(noteIndex);
                }
                onNoteOff: {
                    audio.noteOff(noteIndex);
                }
            }
            NoteButton {
                id: noteD
                noteIndex: 1
                onNoteOn: {
                    audio.noteOn(noteIndex);
                }
                onNoteOff: {
                    audio.noteOff(noteIndex);
                }
            }
            NoteButton {
                id: noteE
                noteIndex: 2
                onNoteOn: {
                    audio.noteOn(noteIndex);
                }
                onNoteOff: {
                    audio.noteOff(noteIndex);
                }
            }
            NoteButton {
                id: noteF
                noteIndex: 3
                onNoteOn: {
                    audio.noteOn(noteIndex);
                }
                onNoteOff: {
                    audio.noteOff(noteIndex);
                }
            }
            NoteButton {
                id: noteG
                noteIndex: 4
                onNoteOn: {
                    audio.noteOn(noteIndex);
                }
                onNoteOff: {
                    audio.noteOff(noteIndex);
                }
            }
            NoteButton {
                id: noteA
                noteIndex: 5
                onNoteOn: {
                    audio.noteOn(noteIndex);
                }
                onNoteOff: {
                    audio.noteOff(noteIndex);
                }
            }
            NoteButton {
                id: noteH
                noteIndex: 6
                onNoteOn: {
                    audio.noteOn(noteIndex);
                }
                onNoteOff: {
                    audio.noteOff(noteIndex);
                }
            }
        }
    }
}
