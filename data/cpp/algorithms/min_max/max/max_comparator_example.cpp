#include <iostream>
#include <algorithm>
#include <string>

int main() {
    std::string s1 = "apple";
    std::string s2 = "banana";

    // Сравнение по длине строк
    auto comp = [](const std::string& a, const std::string& b) {
        return a.length() < b.length();
    };

    const std::string& max_str = std::max(s1, s2, comp);
    std::cout << "Самая длинная строка: " << max_str << std::endl;

    return 0;
}
