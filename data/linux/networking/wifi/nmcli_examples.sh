# Просмотр списка беспроводных интерфейсов
nmcli device status

# Просмотр списка доступных сетей
nmcli device wifi list

# Подключение к открытой сети
nmcli device wifi connect "FreeWiFi"

# Подключение к защищённой сети
nmcli device wifi connect "MyNetwork" password "my_password"

# Просмотр информации о текущем подключении
nmcli connection show

# Отключение от сети
nmcli device disconnect wlan0

# Удаление подключения
nmcli connection delete "MyNetwork"
