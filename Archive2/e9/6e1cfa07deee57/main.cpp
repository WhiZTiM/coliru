#include <stdexcept>

template<typename T>
class non_null_ptr {
public:
    explicit non_null_ptr(T* ptr) : ptr(ptr) {
        if (ptr == nullptr) {
            throw std::invalid_argument("attempt to initialize non_null_ptr with nullptr");
        }
    }

    // move ctor/assign
    // more ctors to simulate covariance
    // etc

    T* get() const {
        if (ptr == nullptr) {
            throw std::logic_error("attempt to query moved-from value");
        }
        return ptr;
    }

    // operators etc

private:
    T* ptr;
};