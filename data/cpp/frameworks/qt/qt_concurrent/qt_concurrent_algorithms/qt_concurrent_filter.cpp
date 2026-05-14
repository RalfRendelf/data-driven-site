#include <QtConcurrent/QtConcurrent>
#include <QFuture>
#include <QList>
#include <QDebug>

bool isEven(int x) {
    return x % 2 == 0;
}

int main() {
    QList<int> numbers = {1, 2, 3, 4, 5};
    QFuture<QList<int>> future = QtConcurrent::filter(numbers, isEven);
    QList<int> result = future.result();
    qDebug() << result; // [2, 4]
    return 0;
}
