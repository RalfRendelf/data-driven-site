#include <QThread>
#include <QDebug>

class MyThread : public QThread {
    Q_OBJECT

protected:
    void run() override {
        qDebug() << "Поток запущен, входим в цикл событий...";
        
        // Выполняем какую-то инициализацию здесь
        
        exec(); // Останавливает поток здесь и ждет событий/сигналов
        
        qDebug() << "Цикл событий завершен.";
    }
};
