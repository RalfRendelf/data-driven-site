#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    std::vector<int> numbers = {3, 1, 4, 1, 5, 9, 2, 6};

    // Преобразуем вектор в кучу с кастомным компаратором (min-heap)
    auto comp = [](int a, int b) { return a > b; };
    std::make_heap(numbers.begin(), numbers.end(), comp);

    // Выводим элементы min-heap
    for (int num : numbers) {
        std::cout << num << " ";
    }
    std::cout << std::endl;

    return 0;
}
