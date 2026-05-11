#include <iostream>
#include <string>

int main() {
    std::string name;
    int age;

    // Чтение из стандартного ввода
    std::cout << "Введите ваше имя: ";
    std::cin >> name;

    std::cout << "Введите ваш возраст: ";
    std::cin >> age;

    // Запись в стандартный вывод
    std::cout << "Привет, " << name << "! Вам " << age << " лет." << std::endl;

    return 0;
}
