#include <iostream>
#include <filesystem>

namespace fs = std::filesystem;

int main() {
    fs::path dir = "test_dir";

    // Создание директории
    if (fs::create_directory(dir)) {
        std::cout << "Директория создана" << std::endl;
    } else {
        std::cout << "Ошибка создания директории" << std::endl;
    }

    // Удаление директории
    if (fs::remove(dir)) {
        std::cout << "Директория удалена" << std::endl;
    } else {
        std::cout << "Ошибка удаления директории" << std::endl;
    }

    return 0;
}
