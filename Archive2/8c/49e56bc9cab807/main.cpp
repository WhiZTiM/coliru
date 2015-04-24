#include <boost/range/algorithm.hpp>
#include <boost/date_time.hpp>

#include <iostream>

namespace pt = boost::posix_time;

class MyType {
    using Clock = pt::second_clock;
    pt::ptime _ts;

  public:
    MyType(int seconds) : _ts(Clock::local_time() + pt::seconds(seconds)) {}

    pt::ptime GetTime() const { return _ts; }

    friend std::ostream& operator<<(std::ostream& os, MyType const&v) {
        return os << "[" << v._ts << "]";
    }
};

namespace detail {
    template <typename F> struct GreaterBy {
        GreaterBy(F&& f) : _f(std::move(f)) {}

        template <typename A, typename B>
            bool operator()(A const& a, B const& b) const {
                return std::greater<decltype(_f(a))>()(_f(a), _f(b));
            }
      private:
        F _f;
    };
}

template <typename F>
detail::GreaterBy<F> order_by_desc(F&& f) {
    return std::forward<F>(f);
}

int main() {
    std::vector<MyType> values { 1, -3, 77, 130, 12, -99 };

    std::cout << "Before sort: ";
    for (auto& v : values)
        std::cout << v << " ";

    std::sort(values.begin(), values.end(), order_by_desc(std::mem_fn(&MyType::GetTime)));

    std::cout << "\nAfter sort: ";
    for (auto& v : values)
        std::cout << v << " ";
}
