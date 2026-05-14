#include <QtConcurrent/QtConcurrent>
#include <QFutureWatcher>
#include <QDebug>
#include <QThread>

void longTask() {
    QThread::sleep(5); // Симуляция долгой задачи
}

int main() {
    QFuture<void> future = QtConcurrent::run(longTask);
    QFutureWatcher<void> watcher;
    watcher.setFuture(future);

    QObject::connect(&watcher, &QFutureWatcher<void>::finished, []() {
        qDebug() << "Задача завершена";
    });

    // Отмена задачи через 1 секунду
    QTimer::singleShot(1000, &watcher, &QFutureWatcher<void>::cancel);

    return 0;
}
