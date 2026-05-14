#include <QThreadPool>
#include <QRunnable>
#include <QDebug>

class Task : public QRunnable {
public:
    void run() override {
        qDebug() << "Задача выполняется в потоке:" << QThread::currentThreadId();
    }
};

int main() {
    QThreadPool::globalInstance()->start(new Task);
    return 0;
}
