#include <dbus/dbus.h>
#include <stdio.h>

int main() {
    DBusConnection *connection;
    DBusError error;

    // Инициализация ошибки
    dbus_error_init(&error);

    // Подключение к сеансовой шине
    connection = dbus_bus_get(DBUS_BUS_SESSION, &error);
    if (dbus_error_is_set(&error)) {
        fprintf(stderr, "Ошибка подключения: %s\n", error.message);
        dbus_error_free(&error);
        return 1;
    }

    // Проверка подключения
    if (connection == NULL) {
        fprintf(stderr, "Не удалось подключиться к шине\n");
        return 1;
    }

    // Освобождение соединения
    dbus_connection_unref(connection);
    return 0;
}
