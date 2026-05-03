#include <iostream>
#include <vector>
#include <numeric>
#include <functional>
#include <cmath>

int main() {
    std::vector<double> a = {1.0, 2.0, 3.0};
    std::vector<double> b = {4.0, 5.0, 6.0};

    // Вычисляем скалярное произведение квадратов элементов
    double result = std::transform_reduce(
        a.begin(), a.end(), b.begin(), 0.0,
        std::plus<double>(), // Бинарная операция для свёртки (сумма)
        [](double x, double y) { return x * y; } // Бинарная операция для элементов (произведение)
    );

    std::cout << "Скалярное произведение: " << result << std::endl;

    return 0;
}
