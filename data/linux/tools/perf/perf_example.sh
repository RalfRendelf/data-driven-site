# Просмотр списка доступных событий
perf list

# Профилирование программы с записью данных
perf record -g ./my_program
perf record -e cycles,instructions,cache-misses ./my_program

# Просмотр отчёта
perf report

# Просмотр статистики в реальном времени
perf stat ./my_program

# Просмотр топ функций по использованию CPU
perf top
