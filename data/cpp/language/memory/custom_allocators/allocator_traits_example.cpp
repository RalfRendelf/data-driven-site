#include <iostream>
#include <memory>
#include <vector>
#include "debug_allocator.hpp"

// Рекомендация: Используйте std::allocator_traits для унифицированной работы с аллокаторами.
int main() {
    DebugAllocator<int> alloc;
    using traits = std::allocator_traits<DebugAllocator<int>>;

    // Выделение памяти
    int* ptr = traits::allocate(alloc, 10);

    // Конструирование объекта
    traits::construct(alloc, ptr, 42);

    std::cout << *ptr << std::endl;

    // Уничтожение объекта
    traits::destroy(alloc, ptr);

    // Освобождение памяти
    traits::deallocate(alloc, ptr, 10);

    return 0;
}
