#include <iostream>
#include <chrono>

int main() {
    // Получение текущего времени
    auto now = std::chrono::system_clock::now();

    // Преобразование в time_t (для вывода)
    std::time_t now_time = std::chrono::system_clock::to_time_t(now);
    std::cout << "Текущее время: " << std::ctime(&now_time);

    // Добавление 1 часа к текущему времени
    auto one_hour_later = now + std::chrono::hours(1);
    std::time_t later_time = std::chrono::system_clock::to_time_t(one_hour_later);
    std::cout << "Через час: " << std::ctime(&later_time);

    return 0;
}
