#include <iostream>
#include <optional>
#include <string>
#include <cmath>

std::optional<double> parse_double(const std::string& s) {
    try {
        return std::stod(s);
    } catch (...) {
        return std::nullopt;
    }
}

std::optional<double> sqrt_safe(double x) {
    if (x < 0) {
        return std::nullopt;
    }
    return std::sqrt(x);
}

int main() {
    // Цепочка: парсинг -> квадратный корень -> округление
    auto result = parse_double("16.0")
        .and_then(sqrt_safe)
        .transform([](double x) {
            return static_cast<int>(std::round(x));
        })
        .or_else([]() {
            return std::optional<int>(-1); // Значение по умолчанию при ошибке
        });

    std::cout << "Результат: " << *result << std::endl; // 4

    return 0;
}
