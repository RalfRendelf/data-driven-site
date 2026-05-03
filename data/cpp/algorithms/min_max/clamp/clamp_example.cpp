#include <iostream>
#include <algorithm>

int main() {
    int value = 15;
    int low = 10;
    int high = 20;

    int clamped = std::clamp(value, low, high);
    std::cout << "Ограниченное значение: " << clamped << std::endl;

    value = 5;
    clamped = std::clamp(value, low, high);
    std::cout << "Ограниченное значение: " << clamped << std::endl;

    value = 25;
    clamped = std::clamp(value, low, high);
    std::cout << "Ограниченное значение: " << clamped << std::endl;

    return 0;
}
