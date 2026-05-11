#include <iostream>
#include <fstream>
#include <string>

int main() {
    // Запись в файл
    std::ofstream out_file("example.txt");
    if (out_file.is_open()) {
        out_file << "Hello, world!" << std::endl;
        out_file.close();
    }

    // Чтение из файла
    std::ifstream in_file("example.txt");
    if (in_file.is_open()) {
        std::string line;
        while (std::getline(in_file, line)) {
            std::cout << line << std::endl;
        }
        in_file.close();
    }

    return 0;
}
