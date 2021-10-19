import QtQuick
import QtQuick.Window
import QtQuick.Layouts
import QtQuick.Controls

Window {
    width: 600
    height: 400
    visible: true
    title: qsTr("CuteKeys")
    color: "#eeeeee"

    Page {
        anchors.fill: parent;

        header: TabBar {
            id: tabBar
            width: parent.width
            currentIndex: 1

            TabButton {
                text: "Tones"
                font.bold: true
                display: AbstractButton.TextOnly
            }
            TabButton {
                text: "Noises"
                font.bold: true
                display: AbstractButton.TextOnly
            }
        }

        StackLayout {
            anchors.fill: parent
            anchors.margins: 10
            currentIndex: tabBar.currentIndex
            SynthPage {
                id: synth
            }
            DrumPage {
                id: drum
            }
        }
    }
}
