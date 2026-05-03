# Показать ошибки для сервиса nginx за последние 2 часа
journalctl -u nginx.service -p err --since "2 hours ago"

# Показать логи для пользователя root за сегодня
journalctl _UID=0 --since today
