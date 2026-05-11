#include <iostream>
#include <optional>
#include <string>
#include <map>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

std::optional<int> get_int(const json& j, const std::string& key) {
    if (j.contains(key) && j[key].is_number()) {
        return j[key].get<int>();
    }
    return std::nullopt;
}

std::optional<std::string> get_string(const json& j, const std::string& key) {
    if (j.contains(key) && j[key].is_string()) {
        return j[key].get<std::string>();
    }
    return std::nullopt;
}

int main() {
    json j = R"({
        "name": "Alice",
        "age": 30,
        "email": "alice@example.com"
    })"_json;

    auto name = get_string(j, "name");
    auto age = get_int(j, "age");
    auto email = get_string(j, "email");

    auto message = name.and_then([](const std::string& n) {
        return std::optional<std::string>(n + ", ");
    }).and_then([&age](const std::string& prefix) -> std::optional<std::string> {
        return age.transform([&prefix](int a) {
            return prefix + std::to_string(a) + " лет, ";
        });
    }).and_then([&email](const std::string& prefix) -> std::optional<std::string> {
        return email.transform([&prefix](const std::string& e) {
            return prefix + e;
        });
    }).value_or("Неизвестный пользователь");

    std::cout << "Сообщение: " << message << std::endl; // "Alice, 30 лет, alice@example.com"

    return 0;
}
