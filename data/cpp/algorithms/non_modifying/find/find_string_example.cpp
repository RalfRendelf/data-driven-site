#include <iostream>
#include <string>
#include <algorithm>

int main() {
    std::string str = "Hello, world!";
    char target = 'o';

    // Поиск символа в строке
    auto it = std::find(str.begin(), str.end(), target);

    if (it != str.end()) {
        std::cout << "Символ '" << target << "' найден на позиции: "
                  << (it - str.begin()) << std::endl;
    } else {
        std::cout << "Символ '" << target << "' не найден." << std::endl;
    }

    return 0;
}
