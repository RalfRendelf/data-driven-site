# Добавление маршрута с метрикой 100
sudo ip route add 10.0.0.0/8 via 192.168.1.2 dev eth0 metric 100

# Добавление маршрута с метрикой 200 (ниже приоритет)
sudo ip route add 10.0.0.0/8 via 192.168.1.3 dev eth0 metric 200
