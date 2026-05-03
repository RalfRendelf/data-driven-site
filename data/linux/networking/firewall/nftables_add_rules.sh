# Разрешаем входящие соединения на порт 22 (SSH)
sudo nft add rule inet filter input tcp dport 22 accept

# Разрешаем ICMP (ping)
sudo nft add rule inet filter input icmp type echo-request accept

# Разрешаем установленные соединения
sudo nft add rule inet filter input ct state established,related accept

# Устанавливаем политику по умолчанию
sudo nft add rule inet filter input counter drop
sudo nft add rule inet filter forward counter drop
sudo nft add rule inet filter output counter accept
