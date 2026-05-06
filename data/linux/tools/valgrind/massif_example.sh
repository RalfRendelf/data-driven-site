# Запуск программы с Massif
valgrind --tool=massif ./my_program

# Просмотр отчёта с помощью ms_print
ms_print massif.out.12345
