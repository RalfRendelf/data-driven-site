#include <QThreadPool>
#include <QDebug>

int main() {
    QThreadPool *pool = QThreadPool::globalInstance();
    pool->setMaxThreadCount(4); // Устанавливаем максимальное количество потоков
    qDebug() << "Максимальное количество потоков:" << pool->maxThreadCount();
    return 0;
}
