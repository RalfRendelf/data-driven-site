#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    std::vector<int> numbers = {1, 2, 3, 4, 5, 6, 7, 8};

    // Заменяем все чётные числа на 0
    std::replace_if(numbers.begin(), numbers.end(),
                   [](int x) { return x % 2 == 0; }, 0);

    // Выводим результат
    for (int num : numbers) {
        std::cout << num << " ";
    }
    std::cout << std::endl;

    return 0;
}
