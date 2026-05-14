#include <QtConcurrent/QtConcurrent>
#include <QFuture>
#include <QDebug>

int add(int a, int b) {
    return a + b;
}

int main() {
    QFuture<int> future = QtConcurrent::run(add, 10, 20);
    int result = future.result();
    qDebug() << "Результат:" << result; // 30
    return 0;
}
