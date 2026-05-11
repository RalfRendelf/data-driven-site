#include <iostream>
#include <regex>
#include <string>

int main() {
    std::string str = "Hello, world! 123";
    // Шаблон: ищем последовательность из одной или более латинских букв
    std::regex pattern("[a-zA-Z]+");

    // smatch — это специальный контейнер, куда запишется результат поиска
    std::smatch matches;

    // Метод regex_search ищет ПЕРВОЕ подходящее совпадение в любом месте строки.
    // Если совпадение найдено, функция возвращает true, а данные о нем пишет в matches.
    if (std::regex_search(str, matches, pattern)) {
        // matches.str() — выводит текст того, что удалось найти
        std::cout << "Найдено совпадение: " << matches.str() << std::endl;
    }

    return 0;
}
