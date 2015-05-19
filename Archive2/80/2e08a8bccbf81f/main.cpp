#include <boost/thread.hpp>
#include <boost/range.hpp>

namespace detail {
    template <typename R, typename M>
    struct RangeLock {
        RangeLock(R&r, M& m) : _r(r), _l(m) {}
        RangeLock(RangeLock&&) = default;

        using iterator = typename boost::range_iterator<R>::type;
        iterator begin() { using std::begin; return begin(_r); }
        iterator end  () { using std::end;   return end  (_r); }

        using const_iterator = typename boost::range_iterator<R const>::type;
        const_iterator begin() const { using std::begin; return begin(_r); }
        const_iterator end  () const { using std::end;   return end  (_r); }

     private:
        R& _r;
        boost::unique_lock<M> _l;
    };
}

template <typename R, typename M>
    detail::RangeLock<R,M> make_range_lock(R& r, M& mx) { return {r,mx}; }
template <typename R, typename M>
    detail::RangeLock<R const,M> make_range_lock(R const& r, M& mx) { return {r,mx}; }

#include <vector>
#include <map>

int main() {

    boost::mutex mx;

    std::vector<int> const vec { 1, 2 };
    std::map<int, std::string> const map { { 1, "one" }, { 2, "two" } };

    for(int i : make_range_lock(vec, mx))
        std::cout << i << std::endl;

    for(auto& p : make_range_lock(map, mx))
        std::cout << p.second << std::endl;

    for(auto& p : make_range_lock(boost::make_iterator_range(map.equal_range(1)), mx))
        std::cout << p.second << std::endl;

}
