# Запуск программы с Memcheck
valgrind --tool=memcheck --leak-check=full ./my_program

# Запуск с записью в файл
valgrind --tool=memcheck --log-file=valgrind.log ./my_program

# Запуск с отслеживанием происхождения неинициализированных значений
valgrind --tool=memcheck --track-origins=yes ./my_program
