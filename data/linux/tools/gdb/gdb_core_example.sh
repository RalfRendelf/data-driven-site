# Создание core dump (в bash)
ulimit -c unlimited
./my_program  # Программа завершится аварийно и создаст core файл

# Запуск GDB с core dump
gdb ./my_program core
