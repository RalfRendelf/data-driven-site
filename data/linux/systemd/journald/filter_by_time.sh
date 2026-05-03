# Показать логи за последние 2 часа
journalctl --since "2 hours ago"

# Показать логи за сегодня
journalctl --since today

# Показать логи за вчера
journalctl --since yesterday --until today

# Показать логи за конкретный день
journalctl --since "2023-10-01" --until "2023-10-02"

# Показать логи за последние 100 записей
journalctl -n 100
