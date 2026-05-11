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

int main() {
    // Предоставление значения по умолчанию
    auto result = parse_int("abc").or_else([]() {
        return std::optional<int>(0); // Возвращаем значение по умолчанию
    });

    std::cout << "Результат: " << *result << std::endl; // 0

    return 0;
}
