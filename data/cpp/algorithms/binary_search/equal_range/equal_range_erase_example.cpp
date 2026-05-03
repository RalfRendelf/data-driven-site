#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    std::vector<int> numbers = {1, 2, 4, 5, 5, 5, 6, 8, 9};
    int target = 5;

    auto [lower, upper] = std::equal_range(numbers.begin(), numbers.end(), target);

    // Удаляем все вхождения элемента
    numbers.erase(lower, upper);

    // Выводим результат
    for (int num : numbers) {
        std::cout << num << " ";
    }
    std::cout << std::endl;

    return 0;
}
