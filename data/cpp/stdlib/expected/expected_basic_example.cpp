#include <iostream>
#include <expected>
#include <string>

int main() {
    std::expected<int, std::string> result1 = 42; // Успех
    std::expected<int, std::string> result2 = std::unexpected("Ошибка: деление на ноль"); // Ошибка

    if (result1.has_value()) {
        std::cout << "Результат: " << *result1 << std::endl;
    }

    if (!result2.has_value()) {
        std::cout << "Ошибка: " << result2.error() << std::endl;
    }

    return 0;
}
