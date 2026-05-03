sudo nft add table inet filter
sudo nft add chain inet filter input { type filter hook input priority 0 \; }
sudo nft add chain inet filter forward { type filter hook forward priority 0 \; }
sudo nft add chain inet filter output { type filter hook output priority 0 \; }
