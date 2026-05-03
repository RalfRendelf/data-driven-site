#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    std::vector<int> numbers = {1, 2, 4, 5, 5, 5, 6, 8, 9};
    int target = 5;

    auto [lower, upper] = std::equal_range(numbers.begin(), numbers.end(), target);

    std::cout << "Диапазон элементов, равных " << target << ": ["
              << (lower - numbers.begin()) << ", "
              << (upper - numbers.begin()) << ")" << std::endl;

    std::cout << "Количество вхождений: "
              << (upper - lower) << std::endl;

    return 0;
}
