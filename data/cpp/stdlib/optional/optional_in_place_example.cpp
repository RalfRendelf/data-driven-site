#include <iostream>
#include <optional>
#include <vector>

int main() {
    // Конструкция на месте с аргументами
    std::optional<std::vector<int>> opt(std::in_place, {1, 2, 3, 4, 5});

    if (opt) {
        for (int num : *opt) {
            std::cout << num << " ";
        }
        std::cout << std::endl;
    }

    return 0;
}
