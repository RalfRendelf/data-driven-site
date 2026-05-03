# Удалить логи старше 2 недель
sudo journalctl --vacuum-time=2weeks

# Удалить логи, занимающие больше 100 МБ
sudo journalctl --vacuum-size=100M

# Удалить все логи
sudo journalctl --vacuum-time=1s
