import QtQuick.Controls 2.15

Column {
    spacing: 10

    Button {
        text: "Кнопка"
        onClicked: console.log("Кнопка нажата")
    }

    ToolButton {
        icon.source: "icon.png"
    }

    RadioButton {
        text: "Вариант 1"
        checked: true
    }

    CheckBox {
        text: "Флажок"
    }
}
