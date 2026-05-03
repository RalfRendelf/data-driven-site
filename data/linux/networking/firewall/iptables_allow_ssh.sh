# Разрешаем входящие соединения на порт 22 (SSH)
sudo iptables -A INPUT -p tcp --dport 22 -j ACCEPT

# Разрешаем исходящий трафик
sudo iptables -A OUTPUT -j ACCEPT

# Разрешаем входящие соединения для установленных соединений
sudo iptables -A INPUT -m state --state ESTABLISHED,RELATED -j ACCEPT

# Разрешаем ICMP (ping)
sudo iptables -A INPUT -p icmp -j ACCEPT
