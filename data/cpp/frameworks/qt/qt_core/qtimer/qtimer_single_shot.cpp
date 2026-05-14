QTimer *timer = new QTimer(this);
timer->setSingleShot(true);
connect(timer, &QTimer::timeout, []() {
    qDebug() << "Таймер сработал один раз!";
});
timer->start(5000); // Сработает через 5 секунд
