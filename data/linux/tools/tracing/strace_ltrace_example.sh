# Трассировка системных вызовов программы
strace ./my_program

# Трассировка с записью в файл
strace -o strace.log ./my_program

# Трассировка только вызовов open и read
strace -e trace=open,read ./my_program

# Трассировка вызовов библиотек
ltrace ./my_program

# Трассировка с статистикой
strace -c ./my_program
ltrace -c ./my_program
