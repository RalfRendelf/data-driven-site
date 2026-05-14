class MyClass : public QObject {
    Q_OBJECT
    Q_PROPERTY(int value READ value WRITE setValue NOTIFY valueChanged)

public:
    int value() const;
    void setValue(int value);

signals:
    void valueChanged(int newValue);
};
