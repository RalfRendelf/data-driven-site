#include <iostream>
#include <variant>
#include <string>

int main() {
    std::variant<int, double, std::string> var = 42;

    if (auto* p = std::get_if<int>(&var)) {
        std::cout << "var содержит int: " << *p << std::endl;
    }

    if (auto* p = std::get_if<std::string>(&var)) {
        std::cout << "var содержит строку: " << *p << std::endl;
    } else {
        std::cout << "var не содержит строку" << std::endl;
    }

    return 0;
}
