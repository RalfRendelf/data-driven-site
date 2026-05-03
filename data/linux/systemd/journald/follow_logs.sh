# Следить за всеми логами
journalctl -f

# Следить за логами для сервиса nginx
journalctl -u nginx.service -f
