# Проверка статуса hostapd
sudo systemctl status hostapd

# Проверка статуса dnsmasq
sudo systemctl status dnsmasq

# Проверка логов hostapd
journalctl -u hostapd -f

# Проверка логов dnsmasq
journalctl -u dnsmasq -f
