#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    std::vector<int> source = {5, 2, 8, 1, 9, 3, 4, 6, 7};
    std::vector<int> destination(5); // Копируем и сортируем первые 5 элементов

    // Копируем и сортируем первые 5 элементов
    std::partial_sort_copy(source.begin(), source.end(),
                          destination.begin(), destination.end());

    // Выводим результат
    for (int num : destination) {
        std::cout << num << " ";
    }
    std::cout << std::endl;

    return 0;
}
