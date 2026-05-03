# Сохранение правил (для Debian/Ubuntu)
sudo iptables-save > /etc/iptables/rules.v4

# Восстановление правил
sudo iptables-restore < /etc/iptables/rules.v4
