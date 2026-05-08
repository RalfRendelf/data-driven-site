#include <iostream>
#include <vector>
#include <memory>

// Рекомендация: Используйте для простых приложений без специфических требований к памяти.
int main() {
    std::vector<int, std::allocator<int>> vec = {1, 2, 3, 4, 5};

    // Использование стандартного аллокатора
    std::allocator<int> alloc;
    int* ptr = alloc.allocate(10); // Выделение памяти для 10 элементов
    alloc.construct(ptr, 42);     // Конструирование объекта
    std::cout << *ptr << std::endl;
    alloc.destroy(ptr);            // Уничтожение объекта
    alloc.deallocate(ptr, 10);     // Освобождение памяти

    return 0;
}
