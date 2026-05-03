#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    std::vector<int> numbers = {1, 2, 4, 5, 5, 6, 8, 9};
    int target = 5;

    auto it = std::upper_bound(numbers.begin(), numbers.end(), target);

    if (it != numbers.end()) {
        std::cout << "Первый элемент, больший " << target << ": " << *it << std::endl;
    } else {
        std::cout << "Все элементы не больше " << target << std::endl;
    }

    return 0;
}
