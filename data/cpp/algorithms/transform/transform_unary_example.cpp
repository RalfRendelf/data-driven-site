#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

int main() {
    std::vector<double> numbers = {1.0, 2.0, 3.0, 4.0, 5.0};
    std::vector<double> squares(numbers.size());

    // Применяем функцию sqrt ко всем элементам
    std::transform(numbers.begin(), numbers.end(), squares.begin(),
                  [](double x) { return x * x; });

    // Выводим результат
    for (double num : squares) {
        std::cout << num << " ";
    }
    std::cout << std::endl;

    return 0;
}
