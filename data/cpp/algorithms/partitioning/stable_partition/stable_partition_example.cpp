#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    std::vector<int> numbers = {1, 2, 3, 4, 5, 6, 7, 8, 9};

    // Стабильно разделяем на чётные и нечётные числа
    auto it = std::stable_partition(numbers.begin(), numbers.end(),
                                   [](int x) { return x % 2 == 0; });

    // Выводим результат
    std::cout << "Чётные числа: ";
    for (auto i = numbers.begin(); i != it; ++i) {
        std::cout << *i << " ";
    }
    std::cout << std::endl;

    std::cout << "Нечётные числа: ";
    for (auto i = it; i != numbers.end(); ++i) {
        std::cout << *i << " ";
    }
    std::cout << std::endl;

    return 0;
}
