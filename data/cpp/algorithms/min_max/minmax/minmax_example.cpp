#include <iostream>
#include <algorithm>
#include <utility>

int main() {
    int a = 10;
    int b = 20;

    auto [min_val, max_val] = std::minmax(a, b);
    std::cout << "Минимальное значение: " << min_val << std::endl;
    std::cout << "Максимальное значение: " << max_val << std::endl;

    return 0;
}
