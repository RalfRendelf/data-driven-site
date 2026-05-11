#include <iostream>
#include <variant>
#include <string>

int main() {
    std::variant<int, double, std::string> var = 42;

    // Обработка всех возможных типов
    std::visit([](auto&& arg) {
        std::cout << "Значение: " << arg << std::endl;
    }, var);

    // Специализированная обработка для каждого типа
    std::visit([](int i) {
        std::cout << "Целое число: " << i << std::endl;
    }, [](double d) {
        std::cout << "Вещественное число: " << d << std::endl;
    }, [](const std::string& s) {
        std::cout << "Строка: " << s << std::endl;
    }, var);

    return 0;
}
