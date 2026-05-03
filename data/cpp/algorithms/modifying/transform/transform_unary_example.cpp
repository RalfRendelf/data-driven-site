#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

int main() {
    std::vector<double> numbers = {1.0, 4.0, 9.0, 16.0};
    std::vector<double> roots(numbers.size());

    // Применяем sqrt ко всем элементам
    std::transform(numbers.begin(), numbers.end(), roots.begin(),
                  [](double x) { return std::sqrt(x); });

    // Выводим результат
    for (double num : roots) {
        std::cout << num << " ";
    }
    std::cout << std::endl;

    return 0;
}
