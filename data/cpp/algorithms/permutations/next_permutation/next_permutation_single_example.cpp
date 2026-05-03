#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    std::vector<int> numbers = {1, 2, 3};

    std::cout << "Текущая перестановка: ";
    for (int num : numbers) {
        std::cout << num << " ";
    }
    std::cout << std::endl;

    // Генерируем следующую перестановку
    bool has_next = std::next_permutation(numbers.begin(), numbers.end());

    if (has_next) {
        std::cout << "Следующая перестановка: ";
        for (int num : numbers) {
            std::cout << num << " ";
        }
        std::cout << std::endl;
    } else {
        std::cout << "Больше перестановок нет." << std::endl;
    }

    return 0;
}
