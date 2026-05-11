#include <iostream>
#include <expected>
#include <string>
#include <cmath>

std::expected<double, std::string> parse_double(const std::string& s) {
    try {
        return std::stod(s);
    } catch (...) {
        return std::unexpected("Ошибка парсинга числа");
    }
}

std::expected<double, std::string> sqrt_safe(double x) {
    if (x < 0) {
        return std::unexpected("Ошибка: отрицательное число");
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
        .transform_error([](const std::string& error) {
            return "Обработка ошибки: " + error;
        });

    if (result) {
        std::cout << "Результат: " << *result << std::endl; // 4
    } else {
        std::cout << result.error() << std::endl;
    }

    return 0;
}
