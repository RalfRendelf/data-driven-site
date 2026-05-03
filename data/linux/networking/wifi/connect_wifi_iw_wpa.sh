#!/bin/bash

# Настройка интерфейса
INTERFACE="wlan0"
SSID="MyNetwork"
PASSWORD="my_password"

# Просмотр доступных сетей
echo "Scanning for networks..."
sudo iw dev $INTERFACE scan | grep SSID

# Создание конфигурации для wpa_supplicant
echo "Creating wpa_supplicant configuration..."
sudo bash -c "cat > /etc/wpa_supplicant/wpa_supplicant.conf <<EOF
ctrl_interface=DIR=/var/run/wpa_supplicant GROUP=netdev
update_config=1
country=RU

network={
    ssid=\"$SSID\"
    psk=\"$PASSWORD\"
    key_mgmt=WPA-PSK
}
EOF"

# Запуск wpa_supplicant
echo "Starting wpa_supplicant..."
sudo wpa_supplicant -B -i $INTERFACE -c /etc/wpa_supplicant/wpa_supplicant.conf

# Получение IP-адреса через DHCP
echo "Requesting IP address via DHCP..."
sudo dhclient $INTERFACE

# Проверка подключения
echo "Checking connection..."
iw dev $INTERFACE link
