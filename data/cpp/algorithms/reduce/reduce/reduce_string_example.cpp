#include <iostream>
#include <vector>
#include <numeric>
#include <string>

int main() {
    std::vector<std::string> words = {"Hello", " ", "World", "!"};

    // Конкатенируем строки
    std::string result = std::reduce(words.begin(), words.end(), std::string());

    std::cout << "Результат конкатенации: " << result << std::endl;

    return 0;
}
