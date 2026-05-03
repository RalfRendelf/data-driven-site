# Использовать таблицу isp1 по умолчанию
sudo ip rule add from all lookup isp1

# Использовать таблицу isp2 для пакетов с исходным адресом 192.168.1.100
sudo ip rule add from 192.168.1.100 lookup isp2
