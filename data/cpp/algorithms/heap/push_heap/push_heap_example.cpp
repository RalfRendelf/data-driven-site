#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    std::vector<int> numbers = {3, 1, 4, 1, 5, 9, 2, 6};

    // Преобразуем вектор в кучу
    std::make_heap(numbers.begin(), numbers.end());

    // Добавляем новый элемент в кучу
    numbers.push_back(10); // Добавляем элемент в конец вектора
    std::push_heap(numbers.begin(), numbers.end()); // Обновляем кучу

    // Выводим элементы кучи
    for (int num : numbers) {
        std::cout << num << " ";
    }
    std::cout << std::endl;

    return 0;
}
