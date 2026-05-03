# Сохранение правил
sudo nft list ruleset > /etc/nftables.conf

# Восстановление правил
sudo nft -f /etc/nftables.conf
