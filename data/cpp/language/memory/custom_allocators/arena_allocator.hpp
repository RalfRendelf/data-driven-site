#include <memory>
#include <cstdlib>
#include <vector>

template <typename T>
class ArenaAllocator {
public:
    using value_type = T;

    explicit ArenaAllocator(std::size_t size = 4096) {
        arena = static_cast<T*>(::malloc(size * sizeof(T)));
        if (!arena) {
            throw std::bad_alloc();
        }
        current = arena;
        end = arena + size;
    }

    ~ArenaAllocator() {
        ::free(arena);
    }

    template <typename U>
    ArenaAllocator(const ArenaAllocator<U>& other)
        : arena(other.arena), current(other.current), end(other.end) {}

    T* allocate(std::size_t n) {
        if (current + n > end) {
            throw std::bad_alloc();
        }
        T* ptr = current;
        current += n;
        return ptr;
    }

    void deallocate(T* p, std::size_t n) {
        // Не освобождаем память до уничтожения аллокатора
    }

    template <typename U, typename... Args>
    void construct(U* p, Args&&... args) {
        ::new (p) U(std::forward<Args>(args)...);
    }

    void destroy(T* p) {
        p->~T();
    }

    void reset() {
        current = arena;
    }

private:
    T* arena;
    T* current;
    T* end;
};

template <typename T1, typename T2>
bool operator==(const ArenaAllocator<T1>&, const ArenaAllocator<T2>&) {
    return true;
}

template <typename T1, typename T2>
bool operator!=(const ArenaAllocator<T1>&, const ArenaAllocator<T2>&) {
    return false;
}
