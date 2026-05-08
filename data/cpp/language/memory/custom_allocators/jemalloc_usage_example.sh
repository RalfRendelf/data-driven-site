# Рекомендация: Используйте для многопоточных серверов и приложений с высокой нагрузкой.
# Глобальная замена malloc на jemalloc
export LD_PRELOAD=/usr/lib/x86_64-linux-gnu/libjemalloc.so.1
./my_program
