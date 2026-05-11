#include <iostream>
#include <random>

int main() {
    // Инициализация с случайным значением
    std::mt19937 gen1(std::random_device{}());

    // Инициализация с фиксированным значением
    std::mt19937 gen2(42);

    std::uniform_int_distribution<int> dist(1, 6);

    std::cout << "Случайное число (случайное начальное значение): " << dist(gen1) << std::endl;
    std::cout << "Случайное число (фиксированное начальное значение): " << dist(gen2) << std::endl;

    return 0;
}
