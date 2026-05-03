#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

int main() {
    std::vector<std::string> words = {"apple", "banana", "cherry", "date"};

    // Поиск самой длинной строки
    auto comp = [](const std::string& a, const std::string& b) {
        return a.length() < b.length();
    };

    auto max_it = std::max_element(words.begin(), words.end(), comp);

    if (max_it != words.end()) {
        std::cout << "Самая длинная строка: " << *max_it << std::endl;
    }

    return 0;
}
