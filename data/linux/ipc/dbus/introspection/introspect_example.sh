# Получение XML-описания с помощью dbus-send
dbus-send --session --dest=org.example.MyService \
  --type=method_call --print-reply /org/example/MyService \
  org.freedesktop.DBus.Introspectable.Introspect

# Получение XML-описания с помощью gdbus
gdbus call --session --dest org.example.MyService \
  --object-path /org/example/MyService \
  --method org.freedesktop.DBus.Introspectable.Introspect
