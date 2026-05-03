#include <iostream>
#include <vector>
#include <algorithm>
#include <ranges>

int main() {
    std::vector<int> numbers = {1, 2, 4, 5, 6, 8, 9};
    int target = 5;

    // Ищем нижнюю границу
    auto it = std::ranges::lower_bound(numbers, target);

    if (it != numbers.end()) {
        std::cout << "Первый элемент, не меньший " << target << ": " << *it << std::endl;
    } else {
        std::cout << "Все элементы меньше " << target << std::endl;
    }

    return 0;
}
