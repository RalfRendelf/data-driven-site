# Создаём символическую ссылку
sudo ln -s /etc/nginx/sites-available/default /etc/nginx/sites-enabled/

# Проверяем конфигурацию
sudo nginx -t

# Перезагружаем Nginx
sudo systemctl reload nginx
