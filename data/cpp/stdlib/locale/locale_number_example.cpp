#include <iostream>
#include <locale>
#include <iomanip>

int main() {
    // Установка локали
    std::locale::global(std::locale("en_US.UTF-8"));
    std::cout.imbue(std::locale());

    double num = 1234567.89;

    // Форматирование числа с учётом локали
    std::cout << "Число: " << num << std::endl;

    // Установка немецкой локали
    std::locale::global(std::locale("de_DE.UTF-8"));
    std::cout.imbue(std::locale());

    std::cout << "Число (немецкая локаль): " << num << std::endl;

    return 0;
}
