Rectangle {
    id: rect
    width: 100
    height: 100
    color: "blue"

    SequentialAnimation {
        id: seqAnim
        NumberAnimation { target: rect; property: "x"; to: 200; duration: 1000 }
        NumberAnimation { target: rect; property: "y"; to: 200; duration: 1000 }
    }

    ParallelAnimation {
        id: parAnim
        NumberAnimation { target: rect; property: "x"; to: 200; duration: 1000 }
        NumberAnimation { target: rect; property: "y"; to: 200; duration: 1000 }
    }

    MouseArea {
        anchors.fill: parent
        onClicked: {
            seqAnim.start()
            // или parAnim.start()
        }
    }
}
