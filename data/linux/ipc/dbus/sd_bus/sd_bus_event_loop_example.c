#include <systemd/sd-bus.h>
#include <systemd/sd-event.h>
#include <stdio.h>

static int signal_handler(sd_bus_message *m, void *user_data, sd_bus_error *ret_error) {
    const char *signal_name;
    int new_value;

    ret = sd_bus_message_get_member(m, &signal_name);
    if (ret < 0) return ret;

    ret = sd_bus_message_read(m, "i", &new_value);
    if (ret < 0) return ret;

    printf("Получен сигнал %s с значением %d\n", signal_name, new_value);
    return 0;
}

int main() {
    sd_event *event = NULL;
    sd_bus *bus = NULL;
    int ret;

    // Создание event loop
    ret = sd_event_default(&event);
    if (ret < 0) {
        fprintf(stderr, "Ошибка создания event loop: %s\n", strerror(-ret));
        return 1;
    }

    // Подключение к сеансовой шине
    ret = sd_bus_open_user(&bus);
    if (ret < 0) {
        fprintf(stderr, "Ошибка подключения: %s\n", strerror(-ret));
        return 1;
    }

    // Привязка шины к event loop
    ret = sd_bus_attach_event(bus, event, SD_EVENT_PRIORITY_NORMAL);
    if (ret < 0) {
        fprintf(stderr, "Ошибка привязки шины к event loop: %s\n", strerror(-ret));
        return 1;
    }

    // Подписка на сигнал
    ret = sd_bus_add_match(
        bus,
        NULL,
        "org.example.MyService",
        "/org/example/MyService",
        "org.example.MyService",
        "ValueChanged",
        signal_handler,
        NULL
    );
    if (ret < 0) {
        fprintf(stderr, "Ошибка подписки на сигнал: %s\n", strerror(-ret));
        return 1;
    }

    // Запуск event loop
    ret = sd_event_loop(event);
    if (ret < 0) {
        fprintf(stderr, "Ошибка event loop: %s\n", strerror(-ret));
        return 1;
    }

    // Освобождение ресурсов
    sd_bus_unref(bus);
    sd_event_unref(event);
    return 0;
}
