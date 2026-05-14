QTimer::singleShot(1000, this, []() {
    qDebug() << "Одноразовый таймер через 1 секунду";
});
