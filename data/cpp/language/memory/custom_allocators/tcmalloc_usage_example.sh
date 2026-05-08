# Рекомендация: Используйте для многопоточных приложений с частыми выделениями памяти.
# Глобальная замена malloc на tcmalloc
export LD_PRELOAD=/usr/lib/libtcmalloc.so
./my_program
