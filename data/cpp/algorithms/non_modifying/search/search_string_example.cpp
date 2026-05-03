#include <iostream>
#include <string>
#include <algorithm>

int main() {
    std::string text = "Hello, world! This is a test string.";
    std::string pattern = "test";

    auto it = std::search(text.begin(), text.end(), pattern.begin(), pattern.end());

    if (it != text.end()) {
        std::cout << "Подстрока найдена на позиции: "
                  << (it - text.begin()) << std::endl;
    } else {
        std::cout << "Подстрока не найдена." << std::endl;
    }

    return 0;
}
