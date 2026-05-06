# Перезапуск системного демона D-Bus
sudo systemctl restart dbus

# Просмотр статуса системного демона
sudo systemctl status dbus

# Просмотр логов системной шины
journalctl -u dbus -f
