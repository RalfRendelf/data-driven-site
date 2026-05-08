#include <iostream>
#include <vector>
#include <boost/pool/pool_alloc.hpp>

// Рекомендация: Используйте для многопоточных приложений с высокими требованиями к производительности.
int main() {
    // Использование fast_pool_allocator
    std::vector<int, boost::fast_pool_allocator<int>> vec;

    for (int i = 0; i < 1000; ++i) {
        vec.push_back(i);
    }

    return 0;
}
