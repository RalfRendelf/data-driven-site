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

    // Чтение свойства Version
    ret = sd_bus_get_property(
        bus,                           // Шина
        "org.example.MyService",       // Имя сервиса
        "/org/example/MyService",      // Путь объекта
        "org.example.MyService",       // Интерфейс
        "Version",                     // Свойство
        NULL,                          // Тип свойства (автоматически)
        &version                       // Значение свойства
    );
    if (ret < 0) {
        fprintf(stderr, "Ошибка чтения свойства: %s\n", strerror(-ret));
        return 1;
    }

    printf("Версия: %d\n", version);

    // Освобождение шины
    sd_bus_unref(bus);
    return 0;
}
