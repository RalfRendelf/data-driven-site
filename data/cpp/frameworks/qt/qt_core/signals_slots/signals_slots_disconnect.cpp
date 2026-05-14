disconnect(sender, &Sender::signal, receiver, &Receiver::slot);

// Разъединение всех сигналов от отправителя
disconnect(sender, nullptr, nullptr, nullptr);

// Разъединение всех сигналов к получателю
disconnect(sender, nullptr, receiver, nullptr);
