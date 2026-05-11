#include <iostream>
#include <any>
#include <string>

int main() {
    std::any a = 42;

    try {
        int value = std::any_cast<int>(a);
        std::cout << "Значение: " << value << std::endl;
    } catch (const std::bad_any_cast& e) {
        std::cerr << "Ошибка извлечения: " << e.what() << std::endl;
    }

    // Безопасное извлечение с проверкой типа
    if (a.type() == typeid(int)) {
        int value = std::any_cast<int>(a);
        std::cout << "Значение: " << value << std::endl;
    }

    return 0;
}
