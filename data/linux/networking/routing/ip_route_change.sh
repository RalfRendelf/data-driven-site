sudo ip route del 10.0.0.0/8
sudo ip route add 10.0.0.0/8 via 192.168.1.3 dev eth0
