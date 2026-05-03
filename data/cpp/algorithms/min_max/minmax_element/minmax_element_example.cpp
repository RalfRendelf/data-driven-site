#include <iostream>
#include <vector>
#include <algorithm>
#include <utility>

int main() {
    std::vector<int> numbers = {5, 2, 8, 1, 9, 3};

    auto [min_it, max_it] = std::minmax_element(numbers.begin(), numbers.end());

    if (min_it != numbers.end() && max_it != numbers.end()) {
        std::cout << "Минимальный элемент: " << *min_it << std::endl;
        std::cout << "Максимальный элемент: " << *max_it << std::endl;
    }

    return 0;
}
