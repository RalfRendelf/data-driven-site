#include <iostream>
#include <memory>
#include <string>

std::unique_ptr<std::string> parse_string(const std::string& s) {
    if (s.empty()) {
        return nullptr;
    }
    return std::make_unique<std::string>(s);
}

std::unique_ptr<int> string_to_int(const std::string& s) {
    try {
        return std::make_unique<int>(std::stoi(s));
    } catch (...) {
        return nullptr;
    }
}

int main() {
    // Эмуляция and_then
    auto result = parse_string("42");
    if (result) {
        auto int_result = string_to_int(*result);
        if (int_result) {
            std::cout << "Результат: " << *int_result << std::endl; // 42
        }
    }

    return 0;
}
