#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

int main() {
    std::vector<std::string> words = {"apple", "banana", "cherry", "date"};
    std::string target = "banana";

    // Сравнение без учёта регистра
    auto comp = [](const std::string& a, const std::string& b) {
        return a < b;
    };

    bool found = std::binary_search(words.begin(), words.end(), target, comp);

    std::cout << "Слово '" << target << "' "
              << (found ? "найдено" : "не найдено") << " в диапазоне." << std::endl;

    return 0;
}
