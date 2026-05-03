#include <iostream>
#include <vector>
#include <algorithm>
#include <ranges>

int main() {
    std::vector<int> numbers = {10, 20, 30, 40, 50};
    int target = 30;

    // Поиск элемента в диапазоне
    auto it = std::ranges::find(numbers, target);

    if (it != numbers.end()) {
        std::cout << "Элемент " << target << " найден на позиции: "
                  << (it - numbers.begin()) << std::endl;
    } else {
        std::cout << "Элемент " << target << " не найден." << std::endl;
    }

    return 0;
}
