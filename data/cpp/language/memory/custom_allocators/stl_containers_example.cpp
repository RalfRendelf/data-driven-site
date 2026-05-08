#include <iostream>
#include <vector>
#include <map>
#include <list>
#include "debug_allocator.hpp"
#include "pool_allocator.hpp"
#include "counting_allocator.hpp"

// Рекомендация: Используйте кастомные аллокаторы для оптимизации работы контейнеров.
int main() {
    // Вектор с отладочным аллокатором
    std::vector<int, DebugAllocator<int>> debug_vec;
    debug_vec.push_back(1);
    debug_vec.push_back(2);

    // Список с пул-аллокатором
    std::list<int, PoolAllocator<int>> pool_list;
    pool_list.push_back(3);
    pool_list.push_back(4);

    // Map с аллокатором подсчёта
    std::map<int, std::string, std::less<int>, CountingAllocator<std::pair<const int, std::string>>> counting_map;
    counting_map[1] = "one";
    counting_map[2] = "two";

    // Выводим статистику
    std::cout << "Allocated: " << CountingAllocator<std::pair<const int, std::string>>::get_allocated() << std::endl;
    std::cout << "Allocations: " << CountingAllocator<std::pair<const int, std::string>>::get_allocations() << std::endl;

    return 0;
}
