#include <dbus/dbus.h>
#include <stdio.h>
#include <unistd.h>

DBusHandlerResult handle_message(DBusConnection *connection, DBusMessage *message, void *user_data) {
    if (dbus_message_is_method_call(message, "org.example.MyService", "GetVersion")) {
        DBusMessage *reply;
        int version = 42;

        // Создание ответа
        reply = dbus_message_new_method_return(message);
        dbus_message_append_args(reply, DBUS_TYPE_INT32, &version, DBUS_TYPE_INVALID);

        // Отправка ответа
        dbus_connection_send(connection, reply, NULL);
        dbus_message_unref(reply);

        return DBUS_HANDLER_RESULT_HANDLED;
    }

    return DBUS_HANDLER_RESULT_NOT_YET_HANDLED;
}

int main() {
    DBusConnection *connection;
    DBusError error;

    dbus_error_init(&error);

    // Подключение к сеансовой шине
    connection = dbus_bus_get(DBUS_BUS_SESSION, &error);
    if (dbus_error_is_set(&error)) {
        fprintf(stderr, "Ошибка подключения: %s\n", error.message);
        dbus_error_free(&error);
        return 1;
    }

    // Регистрация обработчика сообщений
    dbus_connection_add_filter(connection, handle_message, NULL, NULL);

    // Запрос имени на шине
    int ret = dbus_bus_request_name(
        connection, "org.example.MyService", DBUS_NAME_FLAG_REPLACE_EXISTING, &error
    );
    if (dbus_error_is_set(&error)) {
        fprintf(stderr, "Ошибка запроса имени: %s\n", error.message);
        dbus_error_free(&error);
        return 1;
    }

    // Цикл обработки сообщений
    while (dbus_connection_read_write_dispatch(connection, 1000)) {
        // Обработка сообщений
    }

    // Освобождение соединения
    dbus_connection_unref(connection);
    return 0;
}
