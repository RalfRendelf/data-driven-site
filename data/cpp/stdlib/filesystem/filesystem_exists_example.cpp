#include <iostream>
#include <filesystem>

namespace fs = std::filesystem;

int main() {
    fs::path path = "file.txt";

    if (fs::exists(path)) {
        std::cout << "Файл существует" << std::endl;
    } else {
        std::cout << "Файл не существует" << std::endl;
    }

    return 0;
}
