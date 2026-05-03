# Показать уникальные значения поля _EXE
journalctl --output=cat | grep _EXE | sort | uniq

# Показать уникальные значения поля SYSLOG_IDENTIFIER
journalctl --output=cat | grep SYSLOG_IDENTIFIER | sort | uniq
