#include <iostream>
#include <variant>
#include <string>

int main() {
    std::variant<int, double, std::string> var = 42;

    // Преобразование значения в строку
    auto transformed = var.transform([](auto x) {
        return std::to_string(x);
    });

    std::visit([](auto&& arg) {
        std::cout << "Преобразованное значение: " << arg << std::endl;
    }, transformed); // "42"

    return 0;
}
