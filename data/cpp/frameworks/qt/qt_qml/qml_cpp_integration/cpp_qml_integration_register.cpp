#include <QQmlEngine>
#include <QQmlContext>

class MyClass : public QObject {
    Q_OBJECT
public:
    explicit MyClass(QObject *parent = nullptr) : QObject(parent) {}

    Q_INVOKABLE int compute(int a, int b) {
        return a + b;
    }
};

int main(int argc, char *argv[]) {
    QGuiApplication app(argc, argv);

    qmlRegisterType<MyClass>("com.example", 1, 0, "MyClass");

    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    return app.exec();
}
