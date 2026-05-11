#include <iostream>
#include <sstream>
#include <string>

int main() {
    std::stringstream ss;

    // Запись в stringstream
    ss << "Hello, " << "world!" << std::endl;
    ss << "Число: " << 42 << std::endl;

    // Чтение из stringstream
    std::string line;
    while (std::getline(ss, line)) {
        std::cout << line << std::endl;
    }

    return 0;
}
