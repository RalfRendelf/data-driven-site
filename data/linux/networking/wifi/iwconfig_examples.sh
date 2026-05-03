# Просмотр информации о всех беспроводных интерфейсах
iwconfig

# Просмотр информации о конкретном интерфейсе
iwconfig wlan0

# Подключение к открытой сети
sudo iwconfig wlan0 essid "MyNetwork"

# Подключение к сети с WEP-шифрованием
sudo iwconfig wlan0 essid "MyNetwork" key "1234567890"

# Установка канала
sudo iwconfig wlan0 channel 6

# Установка режима работы (managed - клиент, ad-hoc - точка-точка)
sudo iwconfig wlan0 mode managed
