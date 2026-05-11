#include <iostream>
#include <locale>
#include <string>
#include <algorithm>

int main() {
    // Установка локали
    std::locale::global(std::locale("en_US.UTF-8"));

    std::string str1 = "apple";
    std::string str2 = "äpple";

    // Сравнение строк с учётом локали
    std::locale loc;
    if (std::use_facet<std::collate<char>>(loc).compare(str1.data(), str1.data() + str1.size(),
                                                      str2.data(), str2.data() + str2.size()) < 0) {
        std::cout << str1 << " < " << str2 << std::endl;
    } else {
        std::cout << str1 << " >= " << str2 << std::endl;
    }

    return 0;
}
