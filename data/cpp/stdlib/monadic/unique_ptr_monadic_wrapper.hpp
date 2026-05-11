#include <memory>
#include <functional>
#include <optional>

template <typename T>
class MonadicUniquePtr {
public:
    MonadicUniquePtr() = default;
    explicit MonadicUniquePtr(std::unique_ptr<T> ptr) : ptr_(std::move(ptr)) {}

    // and_then
    template <typename F>
    auto and_then(F&& f) -> MonadicUniquePtr<decltype(f(std::declval<T&>()))> {
        if (ptr_) {
            return MonadicUniquePtr<decltype(f(*ptr_))>(f(*ptr_));
        }
        return MonadicUniquePtr<decltype(f(std::declval<T&>()))>(nullptr);
    }

    // transform
    template <typename F>
    auto transform(F&& f) -> MonadicUniquePtr<decltype(f(std::declval<T&>()))> {
        if (ptr_) {
            return MonadicUniquePtr<decltype(f(*ptr_))>(std::make_unique<decltype(f(*ptr_))>(f(*ptr_)));
        }
        return MonadicUniquePtr<decltype(f(std::declval<T&>()))>(nullptr);
    }

    // or_else
    template <typename F>
    auto or_else(F&& f) -> MonadicUniquePtr<T> {
        if (!ptr_) {
            ptr_ = f();
        }
        return *this;
    }

    explicit operator bool() const { return ptr_ != nullptr; }
    T& operator*() { return *ptr_; }
    T* operator->() { return ptr_.get(); }
    T* get() { return ptr_.get(); }

private:
    std::unique_ptr<T> ptr_;
};
