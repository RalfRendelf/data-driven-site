#include <iostream>
#include <variant>
#include <string>

int main() {
    std::variant<int, double, std::string> var = "Hello";

    if (std::holds_alternative<std::string>(var)) {
        std::cout << "var содержит строку: " << std::get<std::string>(var) << std::endl;
    }

    if (var.index() == 2) {
        std::cout << "var содержит третий тип (std::string)" << std::endl;
    }

    return 0;
}
