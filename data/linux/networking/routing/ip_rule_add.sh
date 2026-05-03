# Использовать таблицу custom_table для пакетов с исходным адресом 192.168.1.100
sudo ip rule add from 192.168.1.100 lookup custom_table
