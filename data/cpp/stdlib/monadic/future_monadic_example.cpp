#include <iostream>
#include <future>
#include <string>

std::future<int> parse_async(const std::string& s) {
    return std::async([s]() {
        try {
            return std::stoi(s);
        } catch (...) {
            throw std::runtime_error("Ошибка парсинга");
        }
    });
}

std::future<int> square_async(int x) {
    return std::async([x]() {
        return x * x;
    });
}

int main() {
    try {
        auto future1 = parse_async("42");
        auto future2 = future1.then([](std::future<int> f) {
            return square_async(f.get());
        });

        std::cout << "Результат: " << future2.get() << std::endl; // 1764
    } catch (const std::exception& e) {
        std::cerr << "Ошибка: " << e.what() << std::endl;
    }

    return 0;
}
