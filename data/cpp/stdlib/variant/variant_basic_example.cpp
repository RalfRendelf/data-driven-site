#include <iostream>
#include <variant>
#include <string>

int main() {
    std::variant<int, double, std::string> var1 = 42; // Содержит int
    std::variant<int, double, std::string> var2 = 3.14; // Содержит double
    std::variant<int, double, std::string> var3 = "Hello"; // Содержит std::string

    std::cout << "var1 содержит: " << std::get<int>(var1) << std::endl;
    std::cout << "var2 содержит: " << std::get<double>(var2) << std::endl;
    std::cout << "var3 содержит: " << std::get<std::string>(var3) << std::endl;

    return 0;
}
