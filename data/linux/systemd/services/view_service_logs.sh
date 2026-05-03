# Просмотр логов сервиса
journalctl -u nginx.service

# Просмотр логов в реальном времени
journalctl -u nginx.service -f

# Просмотр логов за последние 100 строк
journalctl -u nginx.service -n 100

# Просмотр логов с фильтрацией по времени
journalctl -u nginx.service --since "2023-10-01 12:00:00" --until "2023-10-01 13:00:00"
