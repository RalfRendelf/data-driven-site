# Запрос A-записи для домена
dig example.com A

# Запрос AAAA-записи (IPv6)
dig example.com AAAA

# Запрос MX-записей
dig example.com MX

# Запрос TXT-записей
dig example.com TXT

# Запрос к конкретному DNS-серверу
dig @8.8.8.8 example.com

# Подробный вывод
dig example.com +nocmd +noall +answer

# Запрос обратного DNS (PTR)
dig -x 8.8.8.8
