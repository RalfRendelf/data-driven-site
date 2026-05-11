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
    // Преобразование ошибки в более информативное сообщение
    auto result = parse("abc").transform_error([](const std::string& error) {
        return "Фатальная ошибка: " + error;
    });

    if (result) {
        std::cout << "Результат: " << *result << std::endl;
    } else {
        std::cout << "Ошибка: " << result.error() << std::endl; // "Фатальная ошибка: Ошибка парсинга"
    }

    return 0;
}
