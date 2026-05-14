QTimer *timer = new QTimer(this);
connect(timer, &QTimer::timeout, this, &MyClass::handleTimeout);
timer->start(1000); // Срабатывает каждую секунду
