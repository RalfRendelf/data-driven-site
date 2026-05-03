#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

int main() {
    std::vector<std::string> source = {"Hello", "World", "!"};
    std::vector<std::string> destination(3);

    // Перемещаем элементы из source в destination с конца
    std::move_backward(source.begin(), source.end(), destination.end());

    // Выводим результат
    for (const auto& str : destination) {
        std::cout << str << " ";
    }
    std::cout << std::endl;

    return 0;
}
