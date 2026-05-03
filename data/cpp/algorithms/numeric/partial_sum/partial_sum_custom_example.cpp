#include <iostream>
#include <vector>
#include <numeric>
#include <functional>

int main() {
    std::vector<int> numbers = {1, 2, 3, 4, 5};
    std::vector<int> result(numbers.size());

    // Вычисляем префиксные произведения
    std::partial_sum(numbers.begin(), numbers.end(), result.begin(), std::multiplies<int>());

    // Выводим результат
    for (int num : result) {
        std::cout << num << " ";
    }
    std::cout << std::endl;

    return 0;
}
