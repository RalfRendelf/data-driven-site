# Просмотр информации о всех беспроводных интерфейсах
iw dev

# Просмотр информации о конкретном интерфейсе
iw dev wlan0 info

# Просмотр списка доступных сетей
iw dev wlan0 scan | grep SSID

# Подключение к открытой сети
sudo iw dev wlan0 connect "MyNetwork"

# Просмотр информации о текущем подключении
iw dev wlan0 link

# Установка канала
sudo iw dev wlan0 set channel 6

# Установка типа интерфейса (managed, ad-hoc, AP)
sudo iw dev wlan0 set type managed
