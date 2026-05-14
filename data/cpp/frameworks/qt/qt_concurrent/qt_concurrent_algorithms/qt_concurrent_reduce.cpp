#include <QtConcurrent/QtConcurrent>
#include <QFuture>
#include <QList>
#include <QDebug>

int sum(int a, int b) {
    return a + b;
}

int main() {
    QList<int> numbers = {1, 2, 3, 4, 5};
    QFuture<int> future = QtConcurrent::reduce(numbers, sum);
    int result = future.result();
    qDebug() << result; // 15
    return 0;
}
