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

    const std::string& min_str = std::min(s1, s2, comp);
    std::cout << "Самая короткая строка: " << min_str << std::endl;

    return 0;
}
