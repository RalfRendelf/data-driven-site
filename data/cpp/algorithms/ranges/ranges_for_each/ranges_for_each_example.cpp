#include <iostream>
#include <vector>
#include <algorithm>
#include <ranges>

int main() {
    std::vector<int> numbers = {1, 2, 3, 4, 5};

    // Применяем функцию к каждому элементу
    std::ranges::for_each(numbers, [](int num) {
        std::cout << num << " ";
    });
    std::cout << std::endl;

    return 0;
}
