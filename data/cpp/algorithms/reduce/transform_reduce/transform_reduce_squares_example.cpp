#include <iostream>
#include <vector>
#include <numeric>
#include <functional>

int main() {
    std::vector<int> numbers = {1, 2, 3, 4, 5};

    // Вычисляем сумму квадратов элементов
    int sum_of_squares = std::transform_reduce(
        numbers.begin(), numbers.end(), 0,
        std::plus<int>(), // Бинарная операция для свёртки (сумма)
        [](int x) { return x * x; } // Унарная операция для преобразования (квадрат)
    );

    std::cout << "Сумма квадратов: " << sum_of_squares << std::endl;

    return 0;
}
