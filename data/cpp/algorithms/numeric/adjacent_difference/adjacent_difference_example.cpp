#include <iostream>
#include <vector>
#include <numeric>

int main() {
    std::vector<int> numbers = {1, 3, 6, 10, 15};
    std::vector<int> differences(numbers.size());

    // Вычисляем разности соседних элементов
    std::adjacent_difference(numbers.begin(), numbers.end(), differences.begin());

    // Выводим результат
    for (int num : differences) {
        std::cout << num << " ";
    }
    std::cout << std::endl;

    return 0;
}
