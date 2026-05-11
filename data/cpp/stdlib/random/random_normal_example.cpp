#include <iostream>
#include <random>

int main() {
    // Создание генератора
    std::mt19937 gen(std::random_device{}());

    // Создание нормального распределения
    std::normal_distribution<double> dist(0.0, 1.0); // Среднее = 0, стандартное отклонение = 1

    // Генерация случайного числа
    double random_number = dist(gen);
    std::cout << "Случайное число с нормальным распределением: " << random_number << std::endl;

    return 0;
}
