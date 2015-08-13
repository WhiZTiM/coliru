#include <cerrno>
#include <system_error>
#include <unistd.h>
#include <utility>

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

enum class operation { read, write };

namespace detail {
    template<typename Self>
    class file_stream_reader {
    public:
        char* read(char* begin, char* end) {
            auto& fd = static_cast<Self*>(this)->fd;
        retry:
            auto n = ::read(fd.native_handle(), begin, end - begin);
            if (n == -1) {
                if (errno == EINTR) {
                    goto retry;
                }
                throw std::system_error(std::make_error_code(static_cast<std::errc>(errno)));
            }
            return begin + n;
        }
    };

    template<typename Self>
    class file_stream_writer {
    public:
        char const* write(char const* begin, char const* end) {
            auto& fd = static_cast<Self*>(this)->fd;
        retry:
            auto n = ::write(fd.native_handle(), begin, end - begin);
            if (n == -1) {
                if (errno == EINTR) {
                    goto retry;
                }
                throw std::system_error(std::make_error_code(static_cast<std::errc>(errno)));
            }
            return begin + n;
        }
    };

    template<operation op, typename... Args>
    struct mixin_for_operation;

    template<typename... Args>
    struct mixin_for_operation<operation::read, Args...> {
        using type = file_stream_reader<Args...>;
    };

    template<typename... Args>
    struct mixin_for_operation<operation::write, Args...> {
        using type = file_stream_writer<Args...>;
    };
}

template<typename FD, operation... supported_operations>
class file_stream : public detail::mixin_for_operation<supported_operations, file_stream<FD, supported_operations...>>::type... {
public:
    explicit file_stream(FD fd_) : fd(std::move(fd_)) { }

private:
    FD fd;

    friend class detail::file_stream_reader<file_stream>;
    friend class detail::file_stream_writer<file_stream>;
};

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main() {
    file_stream<unique_fd, operation::write> stream(unique_fd(open("hi.txt", O_WRONLY | O_CREAT)));
    char data[] = "Hello, world!\n";
    stream.write(data, data + sizeof(data));
    return 0;
}