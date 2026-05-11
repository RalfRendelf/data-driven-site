#include <iostream>
#include <expected>
#include <string>

std::expected<int, std::string> parse_number(const std::string& s) {
    try {
        return std::stoi(s);
    } catch (const std::invalid_argument&) {
        return std::unexpected("Некорректный аргумент");
    } catch (const std::out_of_range&) {
        return std::unexpected("Число вне диапазона");
    }
}

int main() {
    auto result1 = parse_number("42");
    auto result2 = parse_number("abc");

    if (result1) {
        std::cout << "Число: " << *result1 << std::endl;
    }

    if (!result2) {
        std::cout << "Ошибка: " << result2.error() << std::endl;
    }

    return 0;
}
