#include <boost/asio.hpp>
#include <functional>
#include <memory>
#include <utility>
#include <iostream>
#include <stdexcept>
#include <boost/optional.hpp>

template<typename F, typename G>
constexpr auto composite(F&& f, G&& g) {
    return [f, g](auto&&... xs) -> decltype(auto) {
        return g(f(xs...));
    };
}

template<typename T>
class result {
public:
    /* implicit */ result(std::exception exception) : exception_{std::move(exception)} {}
    
    result(T value) : value_{std::move(value)} {}
    
    const T& get() const {
        if (exception_) {
            throw exception_;
        }
        return *value_;   
    }
    
private:
    const boost::optional<const std::exception> exception_;
    const boost::optional<const T> value_;
};

template<>
class result<void> {
public:
    result() {}

    /* implicit */ result(std::exception exception) : exception_{std::move(exception)} {}
    
private:
    const boost::optional<const std::exception> exception_;
};

template<typename R>
struct invoke_impl {
    template<typename F, typename... As>
    auto operator()(F&& f, As&&... args) const {
        try {
            return result<R>{std::forward<F>(f)(std::forward<As>(args)...)}; 
        }
        catch(const std::exception& e) {
            return result<R>{e}; 
        }
    }
};

template<>
struct invoke_impl<void> {
    template<typename F, typename... As>
    auto operator()(F&& f, As&&... args) const {
        try {
            std::forward<F>(f)(std::forward<As>(args)...);
            return result<void>{}; 
        }
        catch(const std::exception& e) {
            return result<void>{e}; 
        }
    }
};

template<typename T> class continuation;

template<typename F>
auto make_continuation(F&& func) {
    return continuation<F>{std::forward<F>(func)};   
}

template<typename F>
struct continuation {
    continuation(F&& func) : func{std::forward<F>(func)} {}
    
    template<typename... As>
    auto operator()(As&&... args) const {
        return invoke_impl<decltype(func(std::forward<As>(args)...))>{}(func, std::forward<As>(args)...);
    }
    
    template<typename G>
    auto and_then(G&& g) && {
        return make_continuation(composite(*this, std::forward<G>(g)));  
    }
    
    F func;
};

int main(int argc, char* argv[]) {
    boost::asio::io_service io_service{1};
    boost::asio::deadline_timer timer{io_service};
    
    timer.expires_from_now(boost::posix_time::seconds(1));
    timer.async_wait(make_continuation([](auto) { 
        std::cout << "boom" << std::endl;
    }).and_then([](auto) { 
        std::cout << "sraka" << std::endl; 
    }));
    
    return io_service.run();
}
