# Показать логи для конкретного исполняемого файла
journalctl _EXE=/usr/sbin/nginx

# Показать логи для конкретного хоста
journalctl _HOSTNAME=myhost

# Показать логи для конкретного сервиса
journalctl SYSLOG_IDENTIFIER=nginx
