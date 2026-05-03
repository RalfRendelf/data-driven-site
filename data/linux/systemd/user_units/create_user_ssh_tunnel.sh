# Создаём директорию для unit-файлов
mkdir -p ~/.config/systemd/user/

# Создаём unit-файл
nano ~/.config/systemd/user/ssh-tunnel.service

# Перезагружаем конфигурацию systemd
systemctl --user daemon-reload

# Включаем и запускаем сервис
systemctl --user enable ssh-tunnel.service
systemctl --user start ssh-tunnel.service

# Включаем linger
sudo loginctl enable-linger $USER
