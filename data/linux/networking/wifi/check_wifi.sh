# Проверка статуса интерфейса
ip link show wlan0

# Проверка доступных сетей
sudo iw dev wlan0 scan | grep SSID

# Проверка конфигурации wpa_supplicant
cat /etc/wpa_supplicant/wpa_supplicant.conf

# Проверка логов wpa_supplicant
journalctl -u wpa_supplicant -f
