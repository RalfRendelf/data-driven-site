QResource resource(":/images/logo.png");
if (resource.isValid()) {
    QByteArray data = resource.data();
    // Работа с данными
}
