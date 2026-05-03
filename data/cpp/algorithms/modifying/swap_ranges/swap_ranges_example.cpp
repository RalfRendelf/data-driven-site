#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    std::vector<int> a = {1, 2, 3, 4};
    std::vector<int> b = {5, 6, 7, 8};

    // Меняем местами элементы a и b
    std::swap_ranges(a.begin(), a.end(), b.begin());

    // Выводим результат
    std::cout << "a: ";
    for (int num : a) {
        std::cout << num << " ";
    }
    std::cout << std::endl;

    std::cout << "b: ";
    for (int num : b) {
        std::cout << num << " ";
    }
    std::cout << std::endl;

    return 0;
}
