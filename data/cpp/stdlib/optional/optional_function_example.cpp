#include <iostream>
#include <optional>
#include <string>

std::optional<std::string> find_user(int id) {
    if (id == 1) {
        return "Alice";
    } else if (id == 2) {
        return "Bob";
    } else {
        return std::nullopt;
    }
}

int main() {
    auto user1 = find_user(1);
    auto user2 = find_user(2);
    auto user3 = find_user(3);

    if (user1) {
        std::cout << "Пользователь найден: " << *user1 << std::endl;
    }

    if (user2) {
        std::cout << "Пользователь найден: " << *user2 << std::endl;
    }

    if (!user3) {
        std::cout << "Пользователь не найден" << std::endl;
    }

    return 0;
}
