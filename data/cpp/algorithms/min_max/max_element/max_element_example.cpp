#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    std::vector<int> numbers = {5, 2, 8, 1, 9, 3};

    auto max_it = std::max_element(numbers.begin(), numbers.end());

    if (max_it != numbers.end()) {
        std::cout << "Максимальный элемент: " << *max_it << std::endl;
    }

    return 0;
}
