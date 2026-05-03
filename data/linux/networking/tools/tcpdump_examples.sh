# Перехват пакетов на интерфейсе eth0
sudo tcpdump -i eth0

# Перехват только TCP-пакетов
sudo tcpdump -i eth0 tcp

# Перехват пакетов на порту 80
sudo tcpdump -i eth0 port 80

# Перехват пакетов с IP-адреса 192.168.1.100
sudo tcpdump -i eth0 host 192.168.1.100

# Перехват пакетов между двумя хостами
sudo tcpdump -i eth0 host 192.168.1.100 and host 192.168.1.200

# Перехват только HTTP-трафика
sudo tcpdump -i eth0 port 80 -A

# Сохранение перехваченных пакетов в файл
sudo tcpdump -i eth0 -w capture.pcap

# Чтение пакетов из файла
tcpdump -r capture.pcap

# Перехват пакетов с отображением содержимого в ASCII
sudo tcpdump -i eth0 -A

# Перехват пакетов с отображением содержимого в HEX и ASCII
sudo tcpdump -i eth0 -XX

# Перехват только N пакетов
sudo tcpdump -i eth0 -c 10
