#include <QtConcurrent/QtConcurrent>
#include <QFuture>
#include <QList>
#include <QDebug>

int square(int x) {
    return x * x;
}

int main() {
    QList<int> numbers = {1, 2, 3, 4, 5};
    QFuture<QList<int>> future = QtConcurrent::map(numbers, square);
    QList<int> result = future.result();
    qDebug() << result; // [1, 4, 9, 16, 25]
    return 0;
}
