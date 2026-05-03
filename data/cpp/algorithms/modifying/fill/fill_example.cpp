#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    std::vector<int> numbers(5); // Вектор из 5 элементов

    // Заполняем вектор нулями
    std::fill(numbers.begin(), numbers.end(), 0);

    // Выводим результат
    for (int num : numbers) {
        std::cout << num << " ";
    }
    std::cout << std::endl;

    return 0;
}
