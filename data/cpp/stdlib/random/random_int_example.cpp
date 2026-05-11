#include <iostream>
#include <random>

int main() {
    // Создание генератора
    std::mt19937 gen(std::random_device{}());

    // Создание распределения
    std::uniform_int_distribution<int> dist(1, 6);

    // Генерация случайного числа
    int random_number = dist(gen);
    std::cout << "Случайное число от 1 до 6: " << random_number << std::endl;

    return 0;
}
