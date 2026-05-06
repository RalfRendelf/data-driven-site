#include <systemd/sd-bus.h>
#include <stdio.h>

int main() {
    sd_bus *bus = NULL;
    int ret;
    int version;

    // Подключение к сеансовой шине
    ret = sd_bus_open_user(&bus);
    if (ret < 0) {
        fprintf(stderr, "Ошибка подключения: %s\n", strerror(-ret));
        return 1;
    }

    // Вызов метода GetVersion
    ret = sd_bus_call_method(
        bus,                           // Шина
        "org.example.MyService",       // Имя сервиса
        "/org/example/MyService",      // Путь объекта
        "org.example.MyService",       // Интерфейс
        "GetVersion",                  // Метод
        NULL,                          // Входные данные
        NULL,                          // Типы входных данных
        &version                       // Выходные данные
    );
    if (ret < 0) {
        fprintf(stderr, "Ошибка вызова метода: %s\n", strerror(-ret));
        return 1;
    }

    printf("Версия: %d\n", version);

    // Освобождение шины
    sd_bus_unref(bus);
    return 0;
}
