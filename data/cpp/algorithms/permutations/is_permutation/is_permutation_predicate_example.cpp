#include <iostream>
#include <vector>
#include <algorithm>
#include <cctype>

int main() {
    std::string s1 = "Hello";
    std::string s2 = "oellH";

    // Проверка перестановки без учёта регистра
    auto comp = [](char a, char b) {
        return std::tolower(a) == std::tolower(b);
    };

    bool is_perm = std::is_permutation(s1.begin(), s1.end(), s2.begin(), comp);

    std::cout << "s2 является перестановкой s1 (без учёта регистра): "
              << (is_perm ? "true" : "false") << std::endl;

    return 0;
}
