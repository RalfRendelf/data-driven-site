#include <iostream>
#include <vector>
#include "aligned_allocator.hpp"
#include "arena_allocator.hpp"

// Рекомендация: Используйте кастомные аллокаторы для оптимизации работы с кастомными типами.
class MyClass {
public:
    MyClass(int x) : value(x) {}
    void print() const { std::cout << value << std::endl; }
private:
    int value;
};

int main() {
    // Вектор с выравненным аллокатором
    std::vector<MyClass, AlignedAllocator<MyClass, 64>> aligned_vec;
    aligned_vec.emplace_back(1);
    aligned_vec.emplace_back(2);

    // Вектор с ареной
    ArenaAllocator<MyClass> arena_alloc(100);
    std::vector<MyClass, ArenaAllocator<MyClass>> arena_vec(arena_alloc);
    for (int i = 0; i < 10; ++i) {
        arena_vec.emplace_back(i);
    }

    for (const auto& obj : aligned_vec) {
        obj.print();
    }

    return 0;
}
