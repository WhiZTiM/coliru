#include <memory>
#include <stdexcept>
#include <utility>

template<typename T, typename D>
class non_null_unique_ptr {
public:
    non_null_unique_ptr(T* ptr, D d) : ptr(ptr, std::move(d)) {
        if (ptr == nullptr) {
            throw std::invalid_argument("attempt to initialize non_null_unique_ptr with nullptr");
        }
    }

    // move ctor/assign
    // more ctors to simulate covariance
    // etc

    T* get() const {
        if (ptr == nullptr) {
            throw std::logic_error("attempt to query moved-from value");
        }
        return ptr.get();
    }

    // operators etc

private:
    std::unique_ptr<T> ptr;
};