# Запуск программы с Callgrind
valgrind --tool=callgrind ./my_program

# Просмотр отчёта с помощью kcachegrind
kcachegrind callgrind.out.12345
