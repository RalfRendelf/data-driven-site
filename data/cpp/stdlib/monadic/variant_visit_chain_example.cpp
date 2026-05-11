#include <iostream>
#include <variant>
#include <string>
#include <cmath>

std::variant<int, double, std::string> compute(const std::variant<int, double>& input) {
    return std::visit([](auto x) -> std::variant<int, double, std::string> {
        if constexpr (std::is_same_v<decltype(x), int>) {
            return x * x;
        } else if constexpr (std::is_same_v<decltype(x), double>) {
            return std::sqrt(x);
        } else {
            return std::string("Неподдерживаемый тип");
        }
    }, input);
}

int main() {
    std::variant<int, double> input = 16.0;

    auto result = compute(input);

    std::visit([](auto&& arg) {
        std::cout << "Результат: " << arg << std::endl;
    }, result); // 4.0

    return 0;
}
