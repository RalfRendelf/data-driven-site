#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    std::vector<int> source = {1, 2, 3, 4, 5};
    std::vector<int> destination(5); // Заранее выделяем память

    // Копируем элементы из source в destination
    std::copy(source.begin(), source.end(), destination.begin());

    // Выводим результат
    for (int num : destination) {
        std::cout << num << " ";
    }
    std::cout << std::endl;

    return 0;
}
