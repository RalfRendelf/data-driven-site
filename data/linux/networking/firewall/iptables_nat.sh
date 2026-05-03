# Включаем маршрутизацию пакетов
sudo sysctl -w net.ipv4.ip_forward=1

# Настраиваем NAT для исходящего трафика
sudo iptables -t nat -A POSTROUTING -o eth0 -j MASQUERADE
