# Профилирование системных вызовов
perf record -e tracepoint:syscalls:sys_enter_* ./my_program

# Просмотр отчёта
perf report
