class MyClass : public QObject {
    Q_OBJECT
    Q_PROPERTY(int value READ value WRITE setValue NOTIFY valueChanged)

public:
    int value() const { return m_value; }
    void setValue(int value) {
        if (m_value != value) {
            m_value = value;
            emit valueChanged(m_value);
        }
    }

signals:
    void valueChanged(int value);

private:
    int m_value;
};
