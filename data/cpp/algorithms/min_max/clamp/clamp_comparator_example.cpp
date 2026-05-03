#include <iostream>
#include <algorithm>
#include <string>

int main() {
    std::string value = "hello";
    std::string low = "apple";
    std::string high = "zebra";

    // Сравнение по длине строк
    auto comp = [](const std::string& a, const std::string& b) {
        return a.length() < b.length();
    };

    std::string clamped = std::clamp(value, low, high, comp);
    std::cout << "Ограниченная строка: " << clamped << std::endl;

    return 0;
}
