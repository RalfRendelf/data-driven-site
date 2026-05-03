#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    std::vector<int> numbers = {3, 2, 1};

    std::cout << "Текущая перестановка: ";
    for (int num : numbers) {
        std::cout << num << " ";
    }
    std::cout << std::endl;

    // Генерируем предыдущую перестановку
    bool has_prev = std::prev_permutation(numbers.begin(), numbers.end());

    if (has_prev) {
        std::cout << "Предыдущая перестановка: ";
        for (int num : numbers) {
            std::cout << num << " ";
        }
        std::cout << std::endl;
    } else {
        std::cout << "Больше перестановок нет." << std::endl;
    }

    return 0;
}
