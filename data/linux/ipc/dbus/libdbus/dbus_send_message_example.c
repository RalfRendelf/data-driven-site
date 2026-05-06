#include <dbus/dbus.h>
#include <stdio.h>

int main() {
    DBusConnection *connection;
    DBusMessage *message, *reply;
    DBusError error;
    int version;

    dbus_error_init(&error);

    // Подключение к сеансовой шине
    connection = dbus_bus_get(DBUS_BUS_SESSION, &error);
    if (dbus_error_is_set(&error)) {
        fprintf(stderr, "Ошибка подключения: %s\n", error.message);
        dbus_error_free(&error);
        return 1;
    }

    // Создание сообщения для вызова метода
    message = dbus_message_new_method_call(
        "org.example.MyService",  // Имя сервиса
        "/org/example/MyService",  // Путь объекта
        "org.example.MyService",    // Интерфейс
        "GetVersion"               // Метод
    );

    // Отправка сообщения и ожидание ответа
    reply = dbus_connection_send_with_reply_and_block(
        connection, message, -1, &error
    );
    if (dbus_error_is_set(&error)) {
        fprintf(stderr, "Ошибка отправки сообщения: %s\n", error.message);
        dbus_error_free(&error);
        dbus_message_unref(message);
        return 1;
    }

    // Извлечение ответа
    if (dbus_message_get_args(reply, &error, DBUS_TYPE_INT32, &version, DBUS_TYPE_INVALID)) {
        printf("Версия: %d\n", version);
    } else {
        fprintf(stderr, "Ошибка извлечения ответа: %s\n", error.message);
        dbus_error_free(&error);
    }

    // Освобождение ресурсов
    dbus_message_unref(message);
    dbus_message_unref(reply);
    dbus_connection_unref(connection);
    return 0;
}
