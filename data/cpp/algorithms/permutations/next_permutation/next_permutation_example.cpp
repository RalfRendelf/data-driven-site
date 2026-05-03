#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    std::vector<int> numbers = {1, 2, 3};

    // Сортируем диапазон для начала генерации перестановок
    std::sort(numbers.begin(), numbers.end());

    do {
        // Выводим текущую перестановку
        for (int num : numbers) {
            std::cout << num << " ";
        }
        std::cout << std::endl;
    } while (std::next_permutation(numbers.begin(), numbers.end()));

    return 0;
}
