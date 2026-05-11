#include <iostream>
#include <iomanip>

int main() {
    int num = 42;
    double pi = 3.1415926535;

    // Вывод в шестнадцатеричном формате
    std::cout << "Шестнадцатеричное: " << std::hex << num << std::endl;

    // Вывод с фиксированной точностью
    std::cout << "Число Pi: " << std::fixed << std::setprecision(2) << pi << std::endl;

    // Вывод с выравниванием
    std::cout << "Выравнивание: " << std::setw(10) << num << std::endl;

    return 0;
}
