# Определение маршрута до хоста
traceroute google.com

# Определение маршрута с указанием максимального количества хопов
traceroute -m 20 google.com

# Определение маршрута с использованием ICMP (вместо UDP)
traceroute -I google.com

# Определение маршрута с указанием порта
traceroute -p 80 google.com

# Определение маршрута с таймаутом
traceroute -w 2 google.com
