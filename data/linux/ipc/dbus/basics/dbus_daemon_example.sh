# Запуск системного демона (обычно запускается автоматически)
sudo dbus-daemon --system --fork

# Запуск сеансового демона
dbus-daemon --session --fork

# Просмотр запущенных демонов
ps aux | grep dbus-daemon

# Перезапуск системного демона (в systemd)
sudo systemctl restart dbus
