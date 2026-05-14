connect(button, &QPushButton::clicked, []() {
    qDebug() << "Кнопка нажата!";
});

// Лямбда с параметрами
connect(slider, &QSlider::valueChanged, [](int value) {
    qDebug() << "Значение:" << value;
});
