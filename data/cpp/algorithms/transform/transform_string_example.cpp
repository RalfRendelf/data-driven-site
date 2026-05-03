#include <iostream>
#include <vector>
#include <algorithm>
#include <cctype>
#include <string>

int main() {
    std::vector<std::string> words = {"hello", "world", "cpp"};
    std::vector<std::string> upper_words(words.size());

    // Преобразуем строки в верхний регистр
    std::transform(words.begin(), words.end(), upper_words.begin(),
        [](const std::string& s) {
            std::string result = s;
            for (char& c : result) {
                c = std::toupper(c);
            }
            return result;
        });

    // Выводим результат
    for (const auto& word : upper_words) {
        std::cout << word << " ";
    }
    std::cout << std::endl;

    return 0;
}
