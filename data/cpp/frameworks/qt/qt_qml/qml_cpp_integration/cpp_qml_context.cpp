QQmlApplicationEngine engine;
MyClass myClass;
engine.rootContext()->setContextProperty("myClass", &myClass);
engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
