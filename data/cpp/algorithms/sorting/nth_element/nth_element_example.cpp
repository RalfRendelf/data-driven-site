#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    std::vector<int> numbers = {5, 2, 8, 1, 9, 3, 4, 6, 7};

    // Находим элемент на 4-й позиции (0-based index)
    std::nth_element(numbers.begin(), numbers.begin() + 4, numbers.end());

    std::cout << "Элемент на 4-й позиции (медиана для нечётного N): "
              << numbers[4] << std::endl;

    // Выводим диапазон после nth_element
    for (int num : numbers) {
        std::cout << num << " ";
    }
    std::cout << std::endl;

    return 0;
}
