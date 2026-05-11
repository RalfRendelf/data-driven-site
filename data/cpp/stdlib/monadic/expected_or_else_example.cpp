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
    // Обработка ошибки парсинга
    auto result = parse("abc").or_else([](const std::string& error) {
        std::cerr << "Обработка ошибки: " << error << std::endl;
        return std::expected<int, std::string>(0); // Возвращаем значение по умолчанию
    });

    std::cout << "Результат: " << *result << std::endl; // 0

    return 0;
}
