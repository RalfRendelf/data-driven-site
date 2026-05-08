#include <iostream>
#include <memory>
#include "debug_allocator.hpp"

// Рекомендация: Используйте кастомные аллокаторы с умными указателями для автоматического управления памятью.
int main() {
    DebugAllocator<int> alloc;

    // Использование с std::unique_ptr
    std::unique_ptr<int, void(*)(int*)> ptr(
        alloc.allocate(1),
        [&alloc](int* p) { alloc.deallocate(p, 1); }
    );
    alloc.construct(ptr.get(), 42);
    std::cout << *ptr << std::endl;
    alloc.destroy(ptr.get());

    return 0;
}
