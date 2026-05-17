Repeater {
    model: fruitModel
    delegate: Rectangle {
        width: 100
        height: 30
        color: "lightblue"
        Text {
            text: name
            anchors.centerIn: parent
        }
        x: index * 110  // Позиционируем элементы в строку
    }
}
