Rectangle {
    id: rect
    width: 100
    height: 100
    color: "blue"

    PropertyAnimation {
        target: rect
        property: "width"
        from: 100
        to: 200
        duration: 1000
        easing.type: Easing.InOutQuad
    }

    MouseArea {
        anchors.fill: parent
        onClicked: {
            rect.animation.start()
        }
    }
}
