#include <iostream>
#include <regex>
#include <string>

int main() {
    // Исходная строка, в которой будем искать слова
    std::string str = "Hello, world! 123";

    // Шаблон для поиска:
    // [a-zA-Z] — любая буква латинского алфавита (регистр не важен)
    // +        — одна или более букв подряд (формируем целое слово)
    std::regex pattern("[a-zA-Z]+");

    // Итератор words_begin начинает поиск совпадений от начала (begin) до конца (end) строки
    auto words_begin = std::sregex_iterator(str.begin(), str.end(), pattern);
    
    // Пустой итератор words_end — это «маркер конца», сигнализирующий, что совпадений больше нет
    auto words_end = std::sregex_iterator();

    // Цикл проходит по всем найденным совпадениям
    for (std::sregex_iterator i = words_begin; i != words_end; ++i) {
        // Извлекаем текущее найденное совпадение (объект smatch)
        std::smatch match = *i;
        // match.str() возвращает саму найденную подстроку
        std::cout << "Совпадение: " << match.str() << std::endl;
    }

    return 0;
}
