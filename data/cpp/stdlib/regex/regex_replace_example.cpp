#include <iostream>
#include <regex>
#include <string>

int main() {
    // Исходная строка, которую будем изменять
    std::string str = "Hello, world! 123";

    // Шаблон для поиска: ищем любую ОДИНОЧНУЮ цифру от 0 до 9
    // Здесь нет квантификатора (+ или *), поэтому поиск идет посимвольно
    std::regex pattern("[0-9]");

    // Метод regex_replace:
    // 1. Берет исходную строку (str)
    // 2. Ищет в ней всё, что подходит под шаблон (pattern)
    // 3. Заменяет каждое совпадение на строку "X"
    std::string result = std::regex_replace(str, pattern, "X");

    // Вывод итоговой строки
    std::cout << "Результат замены: " << result << std::endl;

    return 0;
}
