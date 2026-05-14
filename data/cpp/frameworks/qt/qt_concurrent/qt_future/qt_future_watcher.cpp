#include <QtConcurrent/QtConcurrent>
#include <QFutureWatcher>
#include <QDebug>

int compute() {
    return 42;
}

int main() {
    QFuture<int> future = QtConcurrent::run(compute);
    QFutureWatcher<int> watcher;
    watcher.setFuture(future);

    QObject::connect(&watcher, &QFutureWatcher<int>::finished, [&]() {
        qDebug() << "Задача завершена. Результат:" << watcher.result();
    });

    return 0;
}
