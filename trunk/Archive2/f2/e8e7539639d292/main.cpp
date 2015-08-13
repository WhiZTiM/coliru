#include <cerrno>
#include <unistd.h>

class unique_fd {
public:
    using native_handle_type = int;

    explicit unique_fd(native_handle_type handle) : handle(handle) { }

    unique_fd(unique_fd&& other) : handle(other.handle) {
        other.handle = -1;
    }

    unique_fd& operator=(unique_fd&& other) {
        this->~unique_fd();
        handle = other.handle;
        other.handle = -1;
        return *this;
    }

    ~unique_fd() {
        while (::close(handle) == -1 && errno == EINTR)
            ;
    }

    native_handle_type native_handle() const {
        return handle;
    }

private:
    native_handle_type handle;
};