cmake_minimum_required(VERSION 3.10)
project(MyProject)

# Указываем стандарт C++
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Добавляем исполняемый файл
add_executable(my_program main.cpp utils.cpp)

# Добавляем библиотеку
add_library(my_library STATIC lib.cpp lib.h)

# Линкуем библиотеку с программой
target_link_libraries(my_program PRIVATE my_library)
