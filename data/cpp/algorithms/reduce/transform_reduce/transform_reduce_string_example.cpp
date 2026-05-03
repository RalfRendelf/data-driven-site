#include <iostream>
#include <vector>
#include <numeric>
#include <string>
#include <cctype>

int main() {
    std::vector<std::string> words = {"hello", "world", "cpp"};

    // Конкатенируем строки в верхнем регистре
    std::string result = std::transform_reduce(
        words.begin(), words.end(), std::string(),
        std::plus<std::string>(), // Бинарная операция для свёртки (конкатенация)
        [](const std::string& s) {
            std::string upper;
            for (char c : s) {
                upper += std::toupper(c);
            }
            return upper;
        } // Унарная операция для преобразования (в верхний регистр)
    );

    std::cout << "Результат: " << result << std::endl;

    return 0;
}
