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

    // Увеличиваем возраст каждого человека на 1
    std::ranges::for_each(people, [](int& age) { age += 1; },
                         [](Person& p) -> int& { return p.age; });

    // Выводим результат
    for (const auto& person : people) {
        std::cout << person.name << ": " << person.age << std::endl;
    }

    return 0;
}
