#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    std::vector<int> numbers = {9, 5, 6, 2, 3, 1, 4, 0}; // Куча нарушена на последнем элементе

    auto it = std::is_heap_until(numbers.begin(), numbers.end());

    if (it != numbers.end()) {
        std::cout << "Свойства кучи нарушены на позиции: "
                  << (it - numbers.begin()) << std::endl;
        std::cout << "Элемент: " << *it << std::endl;
    } else {
        std::cout << "Диапазон является кучей." << std::endl;
    }

    return 0;
}
