#include <memory>
#include <cstdlib>
#include <atomic>

template <typename T>
class CountingAllocator {
public:
    using value_type = T;

    CountingAllocator() = default;

    template <typename U>
    CountingAllocator(const CountingAllocator<U>&) {}

    T* allocate(std::size_t n) {
        T* ptr = static_cast<T*>(::malloc(n * sizeof(T)));
        allocated += n;
        ++allocations;
        return ptr;
    }

    void deallocate(T* p, std::size_t n) {
        ::free(p);
        deallocated += n;
        ++deallocations;
    }

    template <typename U, typename... Args>
    void construct(U* p, Args&&... args) {
        ::new (p) U(std::forward<Args>(args)...);
    }

    void destroy(T* p) {
        p->~T();
    }

    static std::size_t get_allocated() { return allocated; }
    static std::size_t get_deallocated() { return deallocated; }
    static std::size_t get_allocations() { return allocations; }
    static std::size_t get_deallocations() { return deallocations; }

private:
    static std::atomic<std::size_t> allocated;
    static std::atomic<std::size_t> deallocated;
    static std::atomic<std::size_t> allocations;
    static std::atomic<std::size_t> deallocations;
};

template <typename T>
std::atomic<std::size_t> CountingAllocator<T>::allocated{0};

template <typename T>
std::atomic<std::size_t> CountingAllocator<T>::deallocated{0};

template <typename T>
std::atomic<std::size_t> CountingAllocator<T>::allocations{0};

template <typename T>
std::atomic<std::size_t> CountingAllocator<T>::deallocations{0};

template <typename T1, typename T2>
bool operator==(const CountingAllocator<T1>&, const CountingAllocator<T2>&) {
    return true;
}

template <typename T1, typename T2>
bool operator!=(const CountingAllocator<T1>&, const CountingAllocator<T2>&) {
    return false;
}
