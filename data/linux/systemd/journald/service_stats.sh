# Показать количество логов для каждого сервиса
journalctl --output=cat | grep "unit=" | sed 's/.*unit=//' | sort | uniq -c | sort -nr
