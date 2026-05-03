# Просмотр логов для сервиса nginx
journalctl -u nginx.service

# Просмотр логов для сервиса nginx в реальном времени
journalctl -u nginx.service -f
