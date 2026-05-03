#include <iostream>
#include <vector>
#include <numeric>

int main() {
    std::vector<int> numbers = {1, 2, 3, 4, 5};
    std::vector<int> prefix_sums(numbers.size());

    // Вычисляем префиксные суммы
    std::partial_sum(numbers.begin(), numbers.end(), prefix_sums.begin());

    // Выводим результат
    for (int num : prefix_sums) {
        std::cout << num << " ";
    }
    std::cout << std::endl;

    return 0;
}
