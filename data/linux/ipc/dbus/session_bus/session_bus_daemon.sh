# Запуск сеансового демона вручную
eval $(dbus-launch --sh-syntax)
echo $DBUS_SESSION_BUS_ADDRESS

# Просмотр переменных окружения
echo $DBUS_SESSION_BUS_ADDRESS
echo $DBUS_SESSION_BUS_PID
