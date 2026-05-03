#include <iostream>
#include <vector>
#include <algorithm>
#include <ranges>

int main() {
    std::vector<int> a = {1, 2, 3, 4, 5};
    std::vector<int> b = {1, 2, 7, 4, 5};

    auto [it1, it2] = std::ranges::mismatch(a, b);

    if (it1 != a.end() && it2 != b.end()) {
        std::cout << "Первое различие на позиции: "
                  << (it1 - a.begin()) << std::endl;
        std::cout << "Элементы: " << *it1 << " (a) и " << *it2 << " (b)" << std::endl;
    } else {
        std::cout << "Диапазоны равны." << std::endl;
    }

    return 0;
}
