# Запуск clang-tidy для одного файла
clang-tidy my_program.cpp --checks=*

# Запуск clang-tidy для проекта с CMake
cmake -DCMAKE_CXX_CLANG_TIDY="clang-tidy;-checks=*" -B build
cmake --build build

# Запуск clang-tidy с конкретными проверками
clang-tidy my_program.cpp --checks=bugprone-*,modernize-*
