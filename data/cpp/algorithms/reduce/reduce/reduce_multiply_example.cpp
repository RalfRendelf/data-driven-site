#include <iostream>
#include <vector>
#include <numeric>
#include <functional>

int main() {
    std::vector<int> numbers = {1, 2, 3, 4, 5};

    // Умножаем элементы вектора
    int product = std::reduce(numbers.begin(), numbers.end(), 1, std::multiplies<int>());

    std::cout << "Произведение элементов: " << product << std::endl;

    return 0;
}
