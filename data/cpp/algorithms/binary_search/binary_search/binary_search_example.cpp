#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    std::vector<int> numbers = {1, 2, 4, 5, 6, 8, 9};
    int target = 5;

    bool found = std::binary_search(numbers.begin(), numbers.end(), target);

    std::cout << "Элемент " << target << " "
              << (found ? "найден" : "не найден") << " в диапазоне." << std::endl;

    return 0;
}
