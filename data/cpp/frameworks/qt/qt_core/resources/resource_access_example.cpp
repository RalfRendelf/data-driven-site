QFile file(":/images/logo.png");
if (file.open(QIODevice::ReadOnly)) {
    QByteArray data = file.readAll();
    // Работа с данными
}
