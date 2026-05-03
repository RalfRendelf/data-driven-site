#!/bin/bash

# Настройка интерфейса
INTERFACE="wlan0"
SSID="MyHotspot"
PASSWORD="hotspot_password"

# Установка hostapd и dnsmasq
sudo apt update
sudo apt install hostapd dnsmasq

# Настройка hostapd
echo "Configuring hostapd..."
sudo bash -c "cat > /etc/hostapd/hostapd.conf <<EOF
interface=$INTERFACE
driver=nl80211
ssid=$SSID
hw_mode=g
channel=6
wmm_enabled=0
macaddr_acl=0
auth_algs=1
ignore_broadcast_ssid=0
wpa=2
wpa_passphrase=$PASSWORD
wpa_key_mgmt=WPA-PSK
wpa_pairwise=TKIP
rsn_pairwise=CCMP
EOF"

# Настройка dnsmasq
echo "Configuring dnsmasq..."
sudo bash -c "cat > /etc/dnsmasq.conf <<EOF
interface=$INTERFACE
dhcp-range=192.168.42.100,192.168.42.200,255.255.255.0,24h
EOF"

# Настройка IP-адреса для интерфейса
echo "Configuring IP address..."
sudo ifconfig $INTERFACE 192.168.42.1 netmask 255.255.255.0

# Запуск hostapd и dnsmasq
echo "Starting hostapd and dnsmasq..."
sudo systemctl unmask hostapd
sudo systemctl enable hostapd
sudo systemctl start hostapd
sudo systemctl start dnsmasq

# Включение маршрутизации
echo "Enabling IP forwarding..."
sudo sysctl -w net.ipv4.ip_forward=1

# Настройка NAT (если нужно раздавать Интернет)
echo "Configuring NAT..."
sudo iptables -t nat -A POSTROUTING -o eth0 -j MASQUERADE
sudo iptables -A FORWARD -i $INTERFACE -o eth0 -j ACCEPT

# Проверка работы точки доступа
echo "Hotspot is running. SSID: $SSID, Password: $PASSWORD"
