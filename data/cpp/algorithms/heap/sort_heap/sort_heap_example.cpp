#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    std::vector<int> numbers = {3, 1, 4, 1, 5, 9, 2, 6};

    // Преобразуем вектор в кучу
    std::make_heap(numbers.begin(), numbers.end());

    // Сортируем кучу
    std::sort_heap(numbers.begin(), numbers.end());

    // Выводим отсортированные элементы
    for (int num : numbers) {
        std::cout << num << " ";
    }
    std::cout << std::endl;

    return 0;
}
