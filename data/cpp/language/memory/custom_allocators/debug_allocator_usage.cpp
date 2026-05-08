#include <iostream>
#include <vector>
#include "debug_allocator.hpp"

// Рекомендация: Используйте для отладки и тестирования приложений.
int main() {
    {
        std::vector<int, DebugAllocator<int>> vec;
        for (int i = 0; i < 10; ++i) {
            vec.push_back(i);
        }
    } // Здесь будет выведено сообщение об утечках, если они есть

    return 0;
}
