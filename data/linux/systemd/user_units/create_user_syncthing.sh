# Создаём директорию для unit-файлов
mkdir -p ~/.config/systemd/user/

# Создаём unit-файл
nano ~/.config/systemd/user/syncthing.service

# Перезагружаем конфигурацию systemd
systemctl --user daemon-reload

# Включаем и запускаем сервис
systemctl --user enable syncthing.service
systemctl --user start syncthing.service

# Включаем linger
sudo loginctl enable-linger $USER
