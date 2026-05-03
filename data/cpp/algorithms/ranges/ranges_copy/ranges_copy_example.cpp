#include <iostream>
#include <vector>
#include <algorithm>
#include <ranges>

int main() {
    std::vector<int> source = {1, 2, 3, 4, 5};
    std::vector<int> destination(5);

    // Копируем элементы из source в destination
    std::ranges::copy(source, destination.begin());

    // Выводим результат
    for (int num : destination) {
        std::cout << num << " ";
    }
    std::cout << std::endl;

    return 0;
}
