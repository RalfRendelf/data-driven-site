#include <iostream>
#include <filesystem>

namespace fs = std::filesystem;

int main() {
    fs::path path = "/home/user/documents/file.txt";

    std::cout << "Полный путь: " << path.string() << std::endl;
    std::cout << "Имя файла: " << path.filename().string() << std::endl;
    std::cout << "Родительский путь: " << path.parent_path().string() << std::endl;
    std::cout << "Расширение: " << path.extension().string() << std::endl;
    std::cout << "Абсолютный путь: " << (path.is_absolute() ? "Да" : "Нет") << std::endl;

    return 0;
}
