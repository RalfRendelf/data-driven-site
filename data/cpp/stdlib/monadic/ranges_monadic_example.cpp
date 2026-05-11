#include <iostream>
#include <vector>
#include <ranges>
#include <algorithm>
#include <numeric>

int main() {
    std::vector<int> numbers = {1, 2, 3, 4, 5};

    // Цепочка операций: фильтрация -> преобразование -> суммирование
    auto result = numbers
        | std::views::filter([](int x) { return x % 2 == 0; }) // Оставляем чётные числа
        | std::views::transform([](int x) { return x * x; }) // Возводим в квадрат
        | std::ranges::to<std::vector>(); // Преобразуем в вектор

    for (int num : result) {
        std::cout << num << " ";
    }
    std::cout << std::endl; // 4 16

    // Суммирование результата
    auto sum = std::accumulate(result.begin(), result.end(), 0);
    std::cout << "Сумма: " << sum << std::endl; // 20

    return 0;
}
