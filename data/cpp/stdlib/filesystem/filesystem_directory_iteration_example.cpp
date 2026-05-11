#include <iostream>
#include <filesystem>

namespace fs = std::filesystem;

int main() {
    fs::path dir = "."; // Текущая директория

    for (const auto& entry : fs::recursive_directory_iterator(dir)) {
        std::cout << entry.path().string() << std::endl;
    }

    return 0;
}
