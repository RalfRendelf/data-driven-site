#include <iostream>
#include <variant>
#include <string>
#include <vector>
#include <cmath>

using Data = std::variant<int, double, std::string, std::vector<int>>;

void process_data(const Data& data) {
    std::visit([](auto&& arg) {
        using T = std::decay_t<decltype(arg)>;
        if constexpr (std::is_same_v<T, int>) {
            std::cout << "Целое число: " << arg << std::endl;
        } else if constexpr (std::is_same_v<T, double>) {
            std::cout << "Вещественное число: " << arg << std::endl;
        } else if constexpr (std::is_same_v<T, std::string>) {
            std::cout << "Строка: " << arg << std::endl;
        } else if constexpr (std::is_same_v<T, std::vector<int>>) {
            std::cout << "Вектор: ";
            for (int num : arg) {
                std::cout << num << " ";
            }
            std::cout << std::endl;
        }
    }, data);
}

Data transform_data(const Data& data) {
    return std::visit([](auto&& arg) -> Data {
        using T = std::decay_t<decltype(arg)>;
        if constexpr (std::is_same_v<T, int>) {
            return arg * 2;
        } else if constexpr (std::is_same_v<T, double>) {
            return std::sqrt(arg);
        } else if constexpr (std::is_same_v<T, std::string>) {
            return arg + " (преобразовано)";
        } else if constexpr (std::is_same_v<T, std::vector<int>>) {
            std::vector<int> result;
            for (int num : arg) {
                result.push_back(num * num);
            }
            return result;
        }
    }, data);
}

int main() {
    std::vector<Data> data_list = {
        42,
        3.14,
        std::string("Hello"),
        std::vector<int>{1, 2, 3, 4, 5}
    };

    for (const auto& data : data_list) {
        std::cout << "Исходные данные: ";
        process_data(data);

        auto transformed = transform_data(data);
        std::cout << "Преобразованные данные: ";
        process_data(transformed);
        std::cout << std::endl;
    }

    return 0;
}
