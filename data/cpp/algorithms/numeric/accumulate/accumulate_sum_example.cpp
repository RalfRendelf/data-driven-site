#include <iostream>
#include <vector>
#include <numeric>

int main() {
    std::vector<int> numbers = {1, 2, 3, 4, 5};

    // Суммируем элементы вектора
    int sum = std::accumulate(numbers.begin(), numbers.end(), 0);

    std::cout << "Сумма элементов: " << sum << std::endl;

    return 0;
}
