#include <iostream>
#include <vector>
#include <algorithm>
#include <ranges>

struct Person {
    std::string name;
    int age;
};

int main() {
    std::vector<Person> people = {
        {"Alice", 30},
        {"Bob", 25},
        {"Charlie", 35}
    };

    // Поиск человека по имени с использованием проекции
    auto it = std::ranges::find(people, "Bob",
                                [](const Person& p) { return p.name; });

    if (it != people.end()) {
        std::cout << "Найден: " << it->name << ", возраст: " << it->age << std::endl;
    } else {
        std::cout << "Не найден." << std::endl;
    }

    return 0;
}
