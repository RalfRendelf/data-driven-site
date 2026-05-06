# Проверка загрузки сервис-файла
dbus-daemon --session --print-address --fork
dbus-send --session --dest=org.freedesktop.DBus --type=method_call \
  --print-reply /org/freedesktop/DBus org.freedesktop.DBus.ListActivatableNames
