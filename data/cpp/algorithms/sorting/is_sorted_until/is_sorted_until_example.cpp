#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    std::vector<int> numbers = {1, 2, 3, 5, 4, 6, 7};

    auto it = std::is_sorted_until(numbers.begin(), numbers.end());

    if (it != numbers.end()) {
        std::cout << "Нарушение сортировки на позиции: "
                  << (it - numbers.begin()) << std::endl;
        std::cout << "Элементы: " << *(it - 1) << " и " << *it << std::endl;
    } else {
        std::cout << "Диапазон отсортирован." << std::endl;
    }

    return 0;
}
