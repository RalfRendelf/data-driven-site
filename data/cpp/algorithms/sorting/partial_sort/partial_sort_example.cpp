#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    std::vector<int> numbers = {5, 2, 8, 1, 9, 3, 4, 6, 7};

    // Сортируем первые 5 элементов
    std::partial_sort(numbers.begin(), numbers.begin() + 5, numbers.end());

    // Выводим результат
    for (int num : numbers) {
        std::cout << num << " ";
    }
    std::cout << std::endl;

    return 0;
}
