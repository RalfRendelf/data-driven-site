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
    // Преобразование значения в строку
    auto result = parse_int("42").transform([](int x) {
        return std::to_string(x) + " в квадрате = " + std::to_string(x * x);
    });

    if (result) {
        std::cout << *result << std::endl; // "42 в квадрате = 1764"
    } else {
        std::cout << "Значение отсутствует" << std::endl;
    }

    return 0;
}
