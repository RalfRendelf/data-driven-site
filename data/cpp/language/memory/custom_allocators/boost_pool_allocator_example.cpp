#include <iostream>
#include <vector>
#include <boost/pool/pool_alloc.hpp>

// Рекомендация: Используйте для приложений с интенсивным выделением/освобождением памяти.
int main() {
    // Использование pool_allocator для вектора
    std::vector<int, boost::pool_allocator<int>> vec;

    for (int i = 0; i < 1000; ++i) {
        vec.push_back(i);
    }

    // Использование pool_allocator напрямую
    boost::pool_allocator<int> alloc;
    int* ptr = alloc.allocate(10);
    alloc.construct(ptr, 42);
    std::cout << *ptr << std::endl;
    alloc.destroy(ptr);
    alloc.deallocate(ptr, 10);

    return 0;
}
