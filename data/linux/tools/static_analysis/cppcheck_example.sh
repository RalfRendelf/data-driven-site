# Запуск cppcheck для одного файла
cppcheck my_program.cpp

# Запуск cppcheck для проекта
cppcheck --enable=all --inconclusive --std=c++20 ./my_project/

# Запуск cppcheck с подавлением предупреждений
cppcheck --suppress=suppressions.txt ./my_project/
