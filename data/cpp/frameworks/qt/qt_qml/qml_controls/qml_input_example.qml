Column {
    spacing: 10

    TextField {
        placeholderText: "Введите текст"
    }

    TextArea {
        placeholderText: "Введите много текста"
    }

    ComboBox {
        model: ["Вариант 1", "Вариант 2", "Вариант 3"]
    }

    SpinBox {
        from: 0
        to: 100
    }

    Slider {
        from: 0
        to: 100
    }
}
