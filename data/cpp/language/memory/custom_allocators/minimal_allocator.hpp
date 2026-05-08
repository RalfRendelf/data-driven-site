#include <memory>
#include <cstdlib>

template <typename T>
class MinimalAllocator {
public:
    using value_type = T;

    MinimalAllocator() = default;

    template <typename U>
    MinimalAllocator(const MinimalAllocator<U>&) {}

    T* allocate(std::size_t n) {
        return static_cast<T*>(::malloc(n * sizeof(T)));
    }

    void deallocate(T* p, std::size_t n) {
        ::free(p);
    }

    template <typename U, typename... Args>
    void construct(U* p, Args&&... args) {
        ::new (p) U(std::forward<Args>(args)...);
    }

    void destroy(T* p) {
        p->~T();
    }
};

template <typename T1, typename T2>
bool operator==(const MinimalAllocator<T1>&, const MinimalAllocator<T2>&) {
    return true;
}

template <typename T1, typename T2>
bool operator!=(const MinimalAllocator<T1>&, const MinimalAllocator<T2>&) {
    return false;
}
