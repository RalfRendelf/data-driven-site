#include <iostream>
#include <algorithm>
#include <string>
#include <utility>

int main() {
    std::string s1 = "apple";
    std::string s2 = "banana";

    // Сравнение по длине строк
    auto comp = [](const std::string& a, const std::string& b) {
        return a.length() < b.length();
    };

    auto [min_str, max_str] = std::minmax(s1, s2, comp);
    std::cout << "Самая короткая строка: " << min_str << std::endl;
    std::cout << "Самая длинная строка: " << max_str << std::endl;

    return 0;
}
