class MyClass : public QObject {
    Q_OBJECT

signals:
    void valueChanged(int newValue, const QString &text);

public slots:
    void handleValueChanged(int value, const QString &text);
};
