#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <utility>

int main() {
    std::vector<std::string> words = {"apple", "banana", "cherry", "date"};

    // Поиск самой короткой и самой длинной строки
    auto comp = [](const std::string& a, const std::string& b) {
        return a.length() < b.length();
    };

    auto [min_it, max_it] = std::minmax_element(words.begin(), words.end(), comp);

    if (min_it != words.end() && max_it != words.end()) {
        std::cout << "Самая короткая строка: " << *min_it << std::endl;
        std::cout << "Самая длинная строка: " << *max_it << std::endl;
    }

    return 0;
}
