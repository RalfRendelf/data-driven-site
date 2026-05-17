Rectangle {
    id: rect
    width: 100
    height: 100
    color: "blue"
    states: [
        State {
            name: "normal"
        },
        State {
            name: "enlarged"
            PropertyChanges { target: rect; width: 200; height: 200 }
        }
    ]
    transitions: [
        Transition {
            from: "*"
            to: "enlarged"
            PropertyAnimation { property: "width"; duration: 500 }
            PropertyAnimation { property: "height"; duration: 500 }
        }
    ]

    MouseArea {
        anchors.fill: parent
        onClicked: {
            rect.state = rect.state === "normal" ? "enlarged" : "normal"
        }
    }
}
