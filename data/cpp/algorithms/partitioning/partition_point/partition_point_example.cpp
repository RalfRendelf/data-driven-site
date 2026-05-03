#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    std::vector<int> numbers = {2, 4, 6, 8, 1, 3, 5, 7, 9};

    // Разделяем вектор на чётные и нечётные числа
    std::partition(numbers.begin(), numbers.end(),
                  [](int x) { return x % 2 == 0; });

    // Находим точку разделения
    auto it = std::partition_point(numbers.begin(), numbers.end(),
                                  [](int x) { return x % 2 == 0; });

    std::cout << "Точка разделения на позиции: "
              << (it - numbers.begin()) << std::endl;

    return 0;
}
