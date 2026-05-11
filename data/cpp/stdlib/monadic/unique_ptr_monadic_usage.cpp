#include <iostream>
#include <string>
#include "unique_ptr_monadic_wrapper.hpp"

MonadicUniquePtr<std::string> parse_string(const std::string& s) {
    if (s.empty()) {
        return MonadicUniquePtr<std::string>(nullptr);
    }
    return MonadicUniquePtr<std::string>(std::make_unique<std::string>(s));
}

MonadicUniquePtr<int> string_to_int(const std::string& s) {
    try {
        return MonadicUniquePtr<int>(std::make_unique<int>(std::stoi(s)));
    } catch (...) {
        return MonadicUniquePtr<int>(nullptr);
    }
}

int main() {
    auto result = parse_string("42")
        .and_then([](const std::string& s) { return string_to_int(s); })
        .transform([](int x) { return x * x; })
        .or_else([]() { return std::make_unique<int>(0); });

    if (result) {
        std::cout << "Результат: " << *result << std::endl; // 1764
    }

    return 0;
}
