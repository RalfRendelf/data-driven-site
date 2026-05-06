#include <systemd/sd-bus.h>
#include <stdio.h>
#include <signal.h>

static int signal_handler(sd_bus_message *m, void *user_data, sd_bus_error *ret_error) {
    const char *signal_name;
    int new_value;

    // Извлечение имени сигнала
    ret = sd_bus_message_get_member(m, &signal_name);
    if (ret < 0) {
        fprintf(stderr, "Ошибка извлечения имени сигнала: %s\n", strerror(-ret));
        return ret;
    }

    // Извлечение данных сигнала
    ret = sd_bus_message_read(m, "i", &new_value);
    if (ret < 0) {
        fprintf(stderr, "Ошибка извлечения данных сигнала: %s\n", strerror(-ret));
        return ret;
    }

    printf("Получен сигнал %s с значением %d\n", signal_name, new_value);
    return 0;
}

int main() {
    sd_bus *bus = NULL;
    int ret;

    // Подключение к сеансовой шине
    ret = sd_bus_open_user(&bus);
    if (ret < 0) {
        fprintf(stderr, "Ошибка подключения: %s\n", strerror(-ret));
        return 1;
    }

    // Подписка на сигнал ValueChanged
    ret = sd_bus_add_match(
        bus,
        NULL,
        "org.example.MyService",       // Интерфейс
        "/org/example/MyService",      // Путь объекта
        "org.example.MyService",       // Интерфейс
        "ValueChanged",                // Сигнал
        signal_handler,                // Обработчик
        NULL                           // Пользовательские данные
    );
    if (ret < 0) {
        fprintf(stderr, "Ошибка подписки на сигнал: %s\n", strerror(-ret));
        return 1;
    }

    // Запрос имени на шине
    ret = sd_bus_request_name(bus, "org.example.MyClient", 0);
    if (ret < 0) {
        fprintf(stderr, "Ошибка запроса имени: %s\n", strerror(-ret));
        return 1;
    }

    // Цикл обработки сообщений
    while (1) {
        ret = sd_bus_process(bus, NULL);
        if (ret < 0) {
            fprintf(stderr, "Ошибка обработки сообщений: %s\n", strerror(-ret));
            break;
        }
        if (ret == 0) {
            ret = sd_bus_wait(bus, (uint64_t) -1);
            if (ret < 0) {
                fprintf(stderr, "Ошибка ожидания сообщений: %s\n", strerror(-ret));
                break;
            }
        }
    }

    // Освобождение шины
    sd_bus_unref(bus);
    return 0;
}
