ListView {
    width: 200
    height: 300
    model: fruitModel
    delegate: Rectangle {
        width: 180
        height: 40
        color: "lightgray"
        Text {
            text: name
            anchors.centerIn: parent
        }
    }
}
