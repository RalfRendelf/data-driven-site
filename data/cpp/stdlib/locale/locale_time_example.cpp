#include <iostream>
#include <locale>
#include <ctime>
#include <iomanip>

int main() {
    // Установка локали
    std::locale::global(std::locale("en_US.UTF-8"));
    std::cout.imbue(std::locale());

    // Получение текущего времени
    std::time_t now = std::time(nullptr);
    std::tm* time_info = std::localtime(&now);

    // Форматирование времени с учётом локали
    std::cout << "Текущее время: " << std::put_time(time_info, "%c") << std::endl;

    return 0;
}
