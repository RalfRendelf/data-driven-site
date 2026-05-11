#include <iostream>
#include <optional>
#include <string>

int main() {
    std::optional<std::string> opt = "Hello, world!";

    // Доступ через оператор *
    if (opt) {
        std::cout << *opt << std::endl;
    }

    // Доступ через value()
    try {
        std::cout << opt.value() << std::endl;
    } catch (const std::bad_optional_access& e) {
        std::cerr << "Ошибка доступа: " << e.what() << std::endl;
    }

    // Доступ через value_or()
    std::cout << opt.value_or("default") << std::endl;

    return 0;
}
