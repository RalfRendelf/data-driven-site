# Создаём директорию для unit-файлов
mkdir -p ~/.config/systemd/user/

# Создаём unit-файл
nano ~/.config/systemd/user/web-server.service

# Перезагружаем конфигурацию systemd
systemctl --user daemon-reload

# Включаем и запускаем сервис
systemctl --user enable web-server.service
systemctl --user start web-server.service

# Включаем linger для работы после выхода
sudo loginctl enable-linger $USER
