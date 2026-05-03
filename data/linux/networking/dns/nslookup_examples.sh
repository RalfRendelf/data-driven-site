# Запрос A-записи для домена
nslookup example.com

# Запрос к конкретному DNS-серверу
nslookup example.com 8.8.8.8

# Запрос MX-записей
nslookup -type=mx example.com

# Запрос TXT-записей
nslookup -type=txt example.com
