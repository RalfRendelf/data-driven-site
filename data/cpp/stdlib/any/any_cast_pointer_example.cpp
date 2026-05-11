#include <iostream>
#include <any>
#include <string>

int main() {
    std::any a = std::string("Hello");

    if (auto* p = std::any_cast<std::string>(&a)) {
        std::cout << "Значение: " << *p << std::endl;
    } else {
        std::cout << "a не содержит std::string" << std::endl;
    }

    return 0;
}
