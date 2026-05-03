#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    std::vector<int> numbers = {10, 20, 30, 40, 50};
    int target = 30;

    // Поиск элемента
    auto it = std::find(numbers.begin(), numbers.end(), target);

    if (it != numbers.end()) {
        std::cout << "Элемент " << target << " найден на позиции: "
                  << (it - numbers.begin()) << std::endl;
    } else {
        std::cout << "Элемент " << target << " не найден." << std::endl;
    }

    return 0;
}
