#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    std::vector<int> numbers = {1, 2, 4, 5, 6, 8, 9};
    int new_value = 3;

    // Находим позицию для вставки
    auto it = std::lower_bound(numbers.begin(), numbers.end(), new_value);

    // Вставляем элемент
    numbers.insert(it, new_value);

    // Выводим результат
    for (int num : numbers) {
        std::cout << num << " ";
    }
    std::cout << std::endl;

    return 0;
}
