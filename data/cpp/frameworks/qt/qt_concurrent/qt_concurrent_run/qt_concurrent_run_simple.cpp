#include <QtConcurrent/QtConcurrent>
#include <QFuture>
#include <QDebug>

int compute() {
    // Долгая вычислительная задача
    return 42;
}

int main() {
    QFuture<int> future = QtConcurrent::run(compute);
    // Продолжаем работу в основном потоке
    int result = future.result(); // Блокирует до завершения
    qDebug() << "Результат:" << result;
    return 0;
}
