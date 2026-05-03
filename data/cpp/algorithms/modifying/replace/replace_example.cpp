#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    std::vector<int> numbers = {1, 2, 3, 2, 4, 2, 5};

    // Заменяем все вхождения числа 2 на 99
    std::replace(numbers.begin(), numbers.end(), 2, 99);

    // Выводим результат
    for (int num : numbers) {
        std::cout << num << " ";
    }
    std::cout << std::endl;

    return 0;
}
