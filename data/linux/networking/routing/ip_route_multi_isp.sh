# Маршрут по умолчанию для первого провайдера
sudo ip route add default via 192.168.1.1 dev eth0 table isp1

# Маршрут по умолчанию для второго провайдера
sudo ip route add default via 192.168.2.1 dev eth1 table isp2

# Маршрут для определённых адресов через второй провайдер
sudo ip route add 203.0.113.0/24 via 192.168.2.1 dev eth1 table isp2
