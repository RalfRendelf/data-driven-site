# Создаём таблицу для NAT
sudo nft add table inet nat

# Создаём цепочку для POSTROUTING
sudo nft add chain inet nat postrouting { type nat hook postrouting priority 100 \; }

# Добавляем правило для NAT
sudo nft add rule inet nat postrouting oifname "eth0" masquerade
