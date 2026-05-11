#include <iostream>
#include <optional>

int main() {
    std::optional<int> opt1; // Пустой optional
    std::optional<int> opt2 = 42; // Optional с значением

    if (opt1.has_value()) {
        std::cout << "opt1 содержит значение: " << *opt1 << std::endl;
    } else {
        std::cout << "opt1 пуст" << std::endl;
    }

    if (opt2) {
        std::cout << "opt2 содержит значение: " << *opt2 << std::endl;
    }

    return 0;
}
