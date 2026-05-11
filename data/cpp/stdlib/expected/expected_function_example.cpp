#include <iostream>
#include <expected>
#include <string>

std::expected<int, std::string> divide(int a, int b) {
    if (b == 0) {
        return std::unexpected("Ошибка: деление на ноль");
    }
    return a / b;
}

int main() {
    auto result1 = divide(10, 2);
    auto result2 = divide(10, 0);

    if (result1) {
        std::cout << "Результат: " << *result1 << std::endl;
    }

    if (!result2) {
        std::cout << "Ошибка: " << result2.error() << std::endl;
    }

    return 0;
}
