#include <iostream>
#include <optional>
#include <string>

std::optional<int> parse_int(const std::string& s) {
    try {
        return std::stoi(s);
    } catch (...) {
        return std::nullopt;
    }
}

std::optional<int> square(int x) {
    return x * x;
}

int main() {
    // Цепочка операций: парсинг -> возведение в квадрат
    auto result = parse_int("42").and_then(square);

    if (result) {
        std::cout << "Результат: " << *result << std::endl; // 1764
    } else {
        std::cout << "Значение отсутствует" << std::endl;
    }

    // Если парсинг не удался, and_then не вызывается
    auto error_result = parse_int("abc").and_then(square);
    if (!error_result) {
        std::cout << "Значение отсутствует" << std::endl;
    }

    return 0;
}
