# Установка сервис-файла в системную директорию
sudo cp org.example.MyService.service /usr/share/dbus-1/system-services/

# Установка сервис-файла в пользовательскую директорию
mkdir -p ~/.local/share/dbus-1/services/
cp org.example.MyService.service ~/.local/share/dbus-1/services/

# Перезагрузка конфигурации D-Bus
sudo systemctl restart dbus
