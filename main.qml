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
            text: object.text;
        }

        Slider {
            id: gainSlider;
            anchors.top: header.bottom;
            anchors.left: parent.left;
            anchors.right: gainLabel.left;
            anchors.leftMargin: 10;
            anchors.rightMargin: 10;
            stepSize: 0.1
            to: 0
            from: -60
            value: audio.gain;
            onValueChanged: audio.gain = value;
        }

        Text {
            id: gainLabel;
            anchors.top: header.bottom;
            anchors.right: parent.right;
            width: 100;
            verticalAlignment: Text.AlignVCenter
            text: audio.gain.toFixed(1) + " dB";
        }
        Slider {
            id: attackSlider;
            anchors.top: gainSlider.bottom;
            anchors.left: parent.left;
            anchors.right: attackLabel.left;
            anchors.leftMargin: 10;
            anchors.rightMargin: 10;
            stepSize: 1
            to: 2000
            from: 0
            value: audio.attack;
            onValueChanged: audio.attack = value;
        }

        Text {
            id: attackLabel;
            anchors.top: gainSlider.bottom;
            anchors.right: parent.right;
            width: 100;
            verticalAlignment: Text.AlignVCenter
            text: audio.attack.toString() + " ms";
        }
        Slider {
            id: releaseSlider;
            anchors.top: attackSlider.bottom;
            anchors.left: parent.left;
            anchors.right: releaseLabel.left;
            anchors.leftMargin: 10;
            anchors.rightMargin: 10;
            stepSize: 1
            to: 2000
            from: 0
            value: audio.release;
            onValueChanged: audio.release = value;
        }

        Text {
            id: releaseLabel;
            anchors.top: attackSlider.bottom;
            anchors.right: parent.right;
            width: 100;
            verticalAlignment: Text.AlignVCenter
            text: audio.release.toString() + " ms";
        }

        RowLayout {
            anchors.top: releaseSlider.bottom;
            anchors.bottom: parent.bottom;
            anchors.left: parent.left;
            anchors.right: parent.right;
            anchors.margins: 10;
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
