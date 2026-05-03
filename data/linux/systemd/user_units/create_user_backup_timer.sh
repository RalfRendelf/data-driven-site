# Создаём директорию для unit-файлов
mkdir -p ~/.config/systemd/user/

# Создаём unit-файлы
nano ~/.config/systemd/user/backup.service
nano ~/.config/systemd/user/backup.timer

# Перезагружаем конфигурацию systemd
systemctl --user daemon-reload

# Включаем и запускаем таймер
systemctl --user enable backup.timer
systemctl --user start backup.timer

# Включаем linger
sudo loginctl enable-linger $USER
