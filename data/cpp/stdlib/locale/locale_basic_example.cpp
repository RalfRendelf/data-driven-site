#include <iostream>
#include <locale>

int main() {
    // Установка глобальной локали
    std::locale::global(std::locale("en_US.UTF-8"));

    // Применение локали к потоку
    std::cout.imbue(std::locale());

    std::cout << "Локаль установлена: " << std::locale().name() << std::endl;

    return 0;
}
