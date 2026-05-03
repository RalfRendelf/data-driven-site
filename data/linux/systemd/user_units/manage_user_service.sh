# Запуск сервиса
systemctl --user start myapp.service

# Остановка сервиса
systemctl --user stop myapp.service

# Просмотр статуса сервиса
systemctl --user status myapp.service

# Включение сервиса (запуск при входе пользователя)
systemctl --user enable myapp.service

# Отключение сервиса
systemctl --user disable myapp.service
