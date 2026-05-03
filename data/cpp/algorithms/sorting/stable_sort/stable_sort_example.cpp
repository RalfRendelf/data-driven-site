#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

struct Person {
    std::string name;
    int age;
};

int main() {
    std::vector<Person> people = {
        {"Alice", 30},
        {"Bob", 25},
        {"Charlie", 30},
        {"David", 20}
    };

    // Стабильная сортировка по возрасту
    std::stable_sort(people.begin(), people.end(),
                    [](const Person& a, const Person& b) {
                        return a.age < b.age;
                    });

    // Выводим результат
    for (const auto& person : people) {
        std::cout << person.name << " (" << person.age << ") ";
    }
    std::cout << std::endl;

    return 0;
}
