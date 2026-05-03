#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    std::vector<int> numbers = {3, 1, 4, 1, 5, 9, 2, 6};

    // Преобразуем вектор в кучу
    std::make_heap(numbers.begin(), numbers.end());

    // Удаляем максимальный элемент из кучи
    std::pop_heap(numbers.begin(), numbers.end()); // Максимальный элемент перемещается в конец
    int max_element = numbers.back(); // Получаем максимальный элемент
    numbers.pop_back(); // Удаляем его из вектора

    std::cout << "Максимальный элемент: " << max_element << std::endl;

    // Выводим оставшиеся элементы кучи
    for (int num : numbers) {
        std::cout << num << " ";
    }
    std::cout << std::endl;

    return 0;
}
