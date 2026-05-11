#include <iostream>
#include <any>
#include <string>

int main() {
    std::any a1; // Пустой any
    std::any a2 = 42; // Содержит int
    std::any a3 = std::string("Hello"); // Содержит std::string

    if (a1.has_value()) {
        std::cout << "a1 содержит значение" << std::endl;
    } else {
        std::cout << "a1 пуст" << std::endl;
    }

    if (a2.has_value()) {
        std::cout << "a2 содержит значение" << std::endl;
    }

    return 0;
}
