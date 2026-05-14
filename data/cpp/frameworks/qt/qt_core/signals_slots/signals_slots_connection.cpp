// Соединение сигнала с слотом
connect(sender, &Sender::signal, receiver, &Receiver::slot);

// Соединение с лямбда-выражением
connect(sender, &Sender::signal, [](int value) {
    qDebug() << "Получено значение:" << value;
});

// Соединение с статическим методом
connect(sender, &Sender::signal, &MyClass::staticSlot);

// Автоотсоединение (Qt 5+)
connect(sender, &Sender::signal, receiver, &Receiver::slot, Qt::UniqueConnection);
