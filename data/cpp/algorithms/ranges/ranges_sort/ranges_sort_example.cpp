#include <iostream>
#include <vector>
#include <algorithm>
#include <ranges>

int main() {
    std::vector<int> numbers = {5, 2, 8, 1, 9, 3};

    // Сортируем вектор
    std::ranges::sort(numbers);

    // Выводим результат
    for (int num : numbers) {
        std::cout << num << " ";
    }
    std::cout << std::endl;

    return 0;
}
