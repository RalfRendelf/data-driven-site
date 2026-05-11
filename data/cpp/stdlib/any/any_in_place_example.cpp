#include <iostream>
#include <any>
#include <vector>

int main() {
    // Конструкция на месте с аргументами
    std::any a(std::in_place_type<std::vector<int>>, {1, 2, 3, 4, 5});

    if (auto* p = std::any_cast<std::vector<int>>(&a)) {
        for (int num : *p) {
            std::cout << num << " ";
        }
        std::cout << std::endl;
    }

    return 0;
}
