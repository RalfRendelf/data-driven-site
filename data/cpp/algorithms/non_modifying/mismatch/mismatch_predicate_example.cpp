#include <iostream>
#include <string>
#include <algorithm>
#include <cctype>

int main() {
    std::string str1 = "Hello";
    std::string str2 = "hElLo";

    // Сравнение без учёта регистра
    auto caseInsensitiveCompare = [](char a, char b) {
        return std::tolower(a) == std::tolower(b);
    };

    auto mismatchPair = std::mismatch(str1.begin(), str1.end(), str2.begin(),
                                     caseInsensitiveCompare);

    if (mismatchPair.first != str1.end()) {
        std::cout << "Первое несовпадение (без учёта регистра) на позиции: "
                  << (mismatchPair.first - str1.begin()) << std::endl;
    } else {
        std::cout << "Все символы совпадают (без учёта регистра)." << std::endl;
    }

    return 0;
}
