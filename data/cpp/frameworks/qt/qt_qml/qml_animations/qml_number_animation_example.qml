Rectangle {
    id: rect
    width: 100
    height: 100
    color: "red"
    opacity: 0

    NumberAnimation {
        target: rect
        property: "opacity"
        to: 1
        duration: 1000
    }

    MouseArea {
        anchors.fill: parent
        onClicked: {
            rect.animation.start()
        }
    }
}
