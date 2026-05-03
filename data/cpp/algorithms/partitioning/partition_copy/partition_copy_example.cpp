#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    std::vector<int> numbers = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    std::vector<int> evens;
    std::vector<int> odds;

    // Копируем чётные и нечётные числа в разные векторы
    std::partition_copy(numbers.begin(), numbers.end(),
                       std::back_inserter(evens), std::back_inserter(odds),
                       [](int x) { return x % 2 == 0; });

    // Выводим результаты
    std::cout << "Чётные числа: ";
    for (int num : evens) {
        std::cout << num << " ";
    }
    std::cout << std::endl;

    std::cout << "Нечётные числа: ";
    for (int num : odds) {
        std::cout << num << " ";
    }
    std::cout << std::endl;

    return 0;
}
