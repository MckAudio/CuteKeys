import QtQuick
import QtQuick.Controls

Rectangle {
    Canvas {
        id: canvas
        anchors.fill: parent

        property real lastX
        property real lastY
        property bool clear: true

        onPaint: {
            var ctx = getContext('2d')
            ctx.lineWidth = 1.5
            ctx.strokeStyle = 'black'
            if (clear) {
                ctx.fillStyle = 'orange'
                ctx.fillRect(0, 0, width, height)
                ctx.fillStyle = 'white'
                ctx.fillRect(5, 5, width-10, height-10)
                ctx.fill()
                clear = false
            }
            ctx.beginPath()
            ctx.moveTo(lastX, lastY)
            ctx.lineTo(area.mouseX, area.mouseY)
            ctx.stroke()
            lastX = area.mouseX
            lastY = area.mouseY
        }
    }
    MouseArea {
        id: area
        anchors.fill: parent
        onPressed: {
            canvas.lastX = mouseX
            canvas.lastY = mouseY
            canvas.clear = true;
            canvas.requestPaint()
        }
        onPositionChanged: {
            canvas.requestPaint()
        }
    }
}
