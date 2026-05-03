#include <iostream>
#include <algorithm>

int main() {
    int numbers[5] = {1, 2, 3, 4, 5};

    // Заполняем первые 3 элемента значением 0
    std::fill_n(numbers, 3, 0);

    // Выводим результат
    for (int i = 0; i < 5; ++i) {
        std::cout << numbers[i] << " ";
    }
    std::cout << std::endl;

    return 0;
}
