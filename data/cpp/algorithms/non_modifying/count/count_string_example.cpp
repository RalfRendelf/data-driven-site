#include <iostream>
#include <string>
#include <algorithm>

int main() {
    std::string text = "hello world";
    char target = 'l';

    // Подсчёт количества вхождений символа 'l'
    int count = std::count(text.begin(), text.end(), target);

    std::cout << "Символ '" << target << "' встречается " << count << " раз(а)." << std::endl;

    return 0;
}
