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

int main() {
    // Преобразование значения в строку
    auto result = parse("42").transform([](int x) {
        return std::to_string(x) + " в квадрате = " + std::to_string(x * x);
    });

    if (result) {
        std::cout << *result << std::endl; // "42 в квадрате = 1764"
    } else {
        std::cout << "Ошибка: " << result.error() << std::endl;
    }

    return 0;
}
