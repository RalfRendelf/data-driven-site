#include <systemd/sd-bus.h>
#include <stdio.h>

int main() {
    sd_bus *bus = NULL;
    int ret;

    // Подключение к сеансовой шине
    ret = sd_bus_open_user(&bus);
    if (ret < 0) {
        fprintf(stderr, "Ошибка подключения к сеансовой шине: %s\n", strerror(-ret));
        return 1;
    }

    // Подключение к системной шине
    // ret = sd_bus_open_system(&bus);

    // Проверка подключения
    if (bus == NULL) {
        fprintf(stderr, "Не удалось подключиться к шине\n");
        return 1;
    }

    // Освобождение шины
    sd_bus_unref(bus);
    return 0;
}
