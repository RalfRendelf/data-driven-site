#include <iostream>
#include <random>

int main() {
    // Создание генератора
    std::mt19937 gen(std::random_device{}());

    // Создание распределения
    std::uniform_real_distribution<double> dist(0.0, 1.0);

    // Генерация случайного числа
    double random_number = dist(gen);
    std::cout << "Случайное вещественное число от 0.0 до 1.0: " << random_number << std::endl;

    return 0;
}
