#include <boost/range.hpp>
#include <boost/range/adaptors.hpp>
#include <boost/range/algorithm.hpp>
#include <iostream>
#include <vector>

namespace MyRange {
    template <typename R> struct Proxy {
        Proxy(R&& r)      : _r(std::move(r)) {}
        Proxy(R const& r) : _r(r) {}

        template <typename OutContainer> operator OutContainer() const {
            return boost::copy_range<OutContainer>(_r);
        }

        using iterator       = typename boost::range_mutable_iterator<R>::type;
        using const_iterator = typename boost::range_const_iterator<R>::type;

        auto begin() const { return range_begin(_r); }
        auto end()   const { return range_end(_r);   }
        auto begin()       { return range_begin(_r); }
        auto end()         { return range_end(_r);   }

      private:
        R _r;
    };

    template <typename R> auto make_proxy(R&& r) { return Proxy<R>(std::forward<R>(r)); }

    template <typename Range, typename Fun> auto map(Range&& p_range, Fun&& p_fun) {
        return make_proxy(std::forward<Range>(p_range) | boost::adaptors::transformed(std::forward<Fun>(p_fun)));
    }

    template <typename Range, typename Pred> auto filter(Range&& p_range, Pred&& p_pred) {
        return make_proxy(std::forward<Range>(p_range) | boost::adaptors::filtered(std::forward<Pred>(p_pred)));
    }
}

int main() {
    using namespace MyRange;
    {
        std::vector<int> l_in  = {1, 2, 3, 4, 5};
        std::vector<int> l_tmp_out = filter(l_in, [](int p){ return p < 4; });
        std::vector<int> l_out = map(l_tmp_out, [](int p){ return p + 5; });

        boost::copy(l_out, std::ostream_iterator<int>(std::cout << "\nfirst:\t", "; "));
    }

    {
        boost::copy(
                map(
                    filter(
                        std::vector<int> { 1,2,3,4,5 },
                        [](int p){ return p < 4; }),
                    [](int p){ return p + 5; }),
                std::ostream_iterator<int>(std::cout << "\nsecond:\t", "; "));
    }
}
