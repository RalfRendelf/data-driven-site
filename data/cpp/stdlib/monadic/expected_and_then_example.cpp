#include <iostream>
#include <expected>
#include <string>

std::expected<int, std::string> parse(const std::string& s) {
    try {
        return std::stoi(s);
    } catch (...) {
        return std::unexpected("Ошибка парсинга");
    }
}

std::expected<int, std::string> square(int x) {
    return x * x;
}

int main() {
    // Цепочка операций: парсинг -> возведение в квадрат
    auto result = parse("42").and_then(square);

    if (result) {
        std::cout << "Результат: " << *result << std::endl; // 1764
    } else {
        std::cout << "Ошибка: " << result.error() << std::endl;
    }

    // Если парсинг не удался, and_then не вызывается
    auto error_result = parse("abc").and_then(square);
    if (!error_result) {
        std::cout << "Ошибка: " << error_result.error() << std::endl; // "Ошибка парсинга"
    }

    return 0;
}
