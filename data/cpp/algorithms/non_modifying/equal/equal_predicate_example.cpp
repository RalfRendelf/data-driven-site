#include <iostream>
#include <vector>
#include <algorithm>
#include <cctype>

int main() {
    std::string str1 = "Hello";
    std::string str2 = "hElLo";

    // Сравнение без учёта регистра
    auto caseInsensitiveCompare = [](char a, char b) {
        return std::tolower(a) == std::tolower(b);
    };

    bool isEqual = std::equal(str1.begin(), str1.end(), str2.begin(),
                             caseInsensitiveCompare);

    std::cout << "str1 и str2 равны (без учёта регистра): "
              << (isEqual ? "true" : "false") << std::endl;

    return 0;
}
