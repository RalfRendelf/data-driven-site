#include <iostream>
#include <expected>
#include <optional>
#include <string>
#include <vector>

std::optional<std::vector<int>> parse_numbers(const std::string& s) {
    try {
        std::vector<int> numbers;
        size_t pos = 0;
        while (pos < s.size()) {
            size_t next_pos = s.find(',', pos);
            if (next_pos == std::string::npos) {
                next_pos = s.size();
            }
            std::string token = s.substr(pos, next_pos - pos);
            numbers.push_back(std::stoi(token));
            pos = next_pos + 1;
        }
        return numbers;
    } catch (...) {
        return std::nullopt;
    }
}

std::expected<int, std::string> sum_numbers(const std::vector<int>& numbers) {
    if (numbers.empty()) {
        return std::unexpected("Пустой список чисел");
    }
    int sum = 0;
    for (int num : numbers) {
        sum += num;
    }
    return sum;
}

int main() {
    auto result = parse_numbers("1,2,3,4,5")
        .and_then(sum_numbers)
        .transform_error([](const std::string& error) {
            return "Ошибка: " + error;
        });

    if (result) {
        std::cout << "Сумма: " << *result << std::endl; // 15
    } else {
        std::cerr << result.error() << std::endl;
    }

    return 0;
}
