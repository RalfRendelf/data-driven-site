#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    std::vector<int> source = {1, 2, 3, 2, 4, 2, 5};
    std::vector<int> destination(source.size());

    // Копируем элементы, заменяя 2 на 99
    std::replace_copy(source.begin(), source.end(), destination.begin(), 2, 99);

    // Выводим результат
    for (int num : destination) {
        std::cout << num << " ";
    }
    std::cout << std::endl;

    return 0;
}
