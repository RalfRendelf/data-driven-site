class MyButton : public QPushButton {
    Q_OBJECT

public:
    explicit MyButton(QWidget *parent = nullptr) : QPushButton(parent) {}

signals:
    void customSignal(int value); // Объявление сигнала

public slots:
    void customSlot(); // Объявление слота
};
