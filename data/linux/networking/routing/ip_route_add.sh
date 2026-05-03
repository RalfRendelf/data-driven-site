# Добавление маршрута по умолчанию
sudo ip route add default via 192.168.1.1 dev eth0

# Добавление статического маршрута
sudo ip route add 10.0.0.0/8 via 192.168.1.2 dev eth0
