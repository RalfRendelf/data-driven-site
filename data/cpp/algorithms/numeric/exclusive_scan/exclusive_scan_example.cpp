#include <iostream>
#include <vector>
#include <numeric>

int main() {
    std::vector<int> numbers = {1, 2, 3, 4, 5};
    std::vector<int> result(numbers.size());

    // Вычисляем эксклюзивные префиксные суммы
    std::exclusive_scan(numbers.begin(), numbers.end(), result.begin(), 0);

    // Выводим результат
    for (int num : result) {
        std::cout << num << " ";
    }
    std::cout << std::endl;

    return 0;
}
