#include <iostream>
#include <vector>
#include <algorithm>
#include <ranges>
#include <string>

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

    // Сортируем по возрасту с использованием проекции
    std::ranges::sort(people, std::less<>(),
                     [](const Person& p) { return p.age; });

    // Выводим результат
    for (const auto& person : people) {
        std::cout << person.name << " (" << person.age << ") ";
    }
    std::cout << std::endl;

    return 0;
}
