#include <memory>
#include <vector>
#include <cstdlib>

template <typename T, std::size_t PoolSize = 1024>
class PoolAllocator {
public:
    using value_type = T;

    PoolAllocator() {
        pool.reserve(PoolSize);
    }

    template <typename U>
    PoolAllocator(const PoolAllocator<U>&) {}

    T* allocate(std::size_t n) {
        if (pool.empty()) {
            // Выделяем новый блок памяти
            T* block = static_cast<T*>(::malloc(n * sizeof(T)));
            pool.push_back(block);
            return block;
        } else {
            // Используем существующий блок
            T* block = pool.back();
            pool.pop_back();
            return block;
        }
    }

    void deallocate(T* p, std::size_t n) {
        pool.push_back(p);
    }

    template <typename U, typename... Args>
    void construct(U* p, Args&&... args) {
        ::new (p) U(std::forward<Args>(args)...);
    }

    void destroy(T* p) {
        p->~T();
    }

private:
    std::vector<T*> pool;
};

template <typename T1, typename T2>
bool operator==(const PoolAllocator<T1>&, const PoolAllocator<T2>&) {
    return true;
}

template <typename T1, typename T2>
bool operator!=(const PoolAllocator<T1>&, const PoolAllocator<T2>&) {
    return false;
}
