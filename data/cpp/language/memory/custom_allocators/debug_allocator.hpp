#include <memory>
#include <cstdlib>
#include <iostream>
#include <unordered_map>
#include <mutex>

template <typename T>
class DebugAllocator {
public:
    using value_type = T;

    DebugAllocator() = default;

    template <typename U>
    DebugAllocator(const DebugAllocator<U>&) {}

    T* allocate(std::size_t n) {
        T* ptr = static_cast<T*>(::malloc(n * sizeof(T)));
        std::lock_guard<std::mutex> lock(mutex);
        allocations[ptr] = n;
        std::cout << "[DEBUG] Allocated " << n << " elements at " << ptr << std::endl;
        return ptr;
    }

    void deallocate(T* p, std::size_t n) {
        std::lock_guard<std::mutex> lock(mutex);
        auto it = allocations.find(p);
        if (it != allocations.end()) {
            std::cout << "[DEBUG] Deallocated " << it->second << " elements at " << p << std::endl;
            allocations.erase(it);
        } else {
            std::cerr << "[DEBUG] Double free or invalid pointer: " << p << std::endl;
        }
        ::free(p);
    }

    template <typename U, typename... Args>
    void construct(U* p, Args&&... args) {
        ::new (p) U(std::forward<Args>(args)...);
    }

    void destroy(T* p) {
        p->~T();
    }

    ~DebugAllocator() {
        std::lock_guard<std::mutex> lock(mutex);
        if (!allocations.empty()) {
            std::cerr << "[DEBUG] Memory leaks detected:" << std::endl;
            for (const auto& entry : allocations) {
                std::cerr << "[DEBUG] Leaked " << entry.second << " elements at " << entry.first << std::endl;
            }
        }
    }

private:
    static std::unordered_map<void*, std::size_t> allocations;
    static std::mutex mutex;
};

template <typename T>
std::unordered_map<void*, std::size_t> DebugAllocator<T>::allocations;

template <typename T>
std::mutex DebugAllocator<T>::mutex;

template <typename T1, typename T2>
bool operator==(const DebugAllocator<T1>&, const DebugAllocator<T2>&) {
    return true;
}

template <typename T1, typename T2>
bool operator!=(const DebugAllocator<T1>&, const DebugAllocator<T2>&) {
    return false;
}
