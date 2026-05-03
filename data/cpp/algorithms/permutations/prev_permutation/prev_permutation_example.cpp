#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    std::vector<int> numbers = {1, 2, 3};

    // Сортируем диапазон в обратном порядке для начала генерации перестановок
    std::sort(numbers.begin(), numbers.end(), std::greater<int>());

    do {
        // Выводим текущую перестановку
        for (int num : numbers) {
            std::cout << num << " ";
        }
        std::cout << std::endl;
    } while (std::prev_permutation(numbers.begin(), numbers.end()));

    return 0;
}
