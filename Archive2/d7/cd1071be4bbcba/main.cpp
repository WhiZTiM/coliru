#include <iostream>
#include <vector>
#include <map>
#include <tuple>
#include <utility>

namespace detail {
    template <typename... Iterators>
    class zip_iterator
    {
    public:
        using value_type = std::tuple<typename std::iterator_traits<Iterators>::reference...>;
    
        template <typename... T>
        zip_iterator(T... ts)
            : iters(ts...)
        { }
        
        value_type operator*() const {
            return dereference(std::index_sequence_for<Iterators...>{});
        }
        
        zip_iterator& operator++() {
            increment(std::index_sequence_for<Iterators...>{});
            return *this;
        }
        
        zip_iterator operator++(int ) {
            zip_iterator tmp(*this);
            ++*this;
            return tmp;
        }
        
        bool operator==(const zip_iterator& rhs) const {
            return equal(rhs, std::index_sequence_for<Iterators...>{});
        }
        
        bool operator!=(const zip_iterator& rhs) const {
            return !(*this == rhs);
        }
        
    private:
        template <size_t... Is>
        value_type dereference(std::index_sequence<Is...> ) const {
            return value_type{*std::get<Is>(iters)...};
        }
        
        template <size_t... Is>
        void increment(std::index_sequence<Is...> ) {
            int unused[] = {(++std::get<Is>(iters), 0)... };
            (void)unused;
        }
        
        template <size_t... Is>
        bool equal(const zip_iterator& rhs, std::index_sequence<Is...> ) const
        {
            // conservative: stop at the first match
            for (bool b : {std::get<Is>(iters) == std::get<Is>(rhs.iters)...}) {
                if (b) return true;
            }
            return false;
        }
    
        std::tuple<Iterators...> iters;
    };

    template <typename iterator, typename Containers, size_t... Is>
    iterator begin_impl(Containers& cs, std::index_sequence<Is...> ) {
        return iterator(begin(std::get<Is>(cs))...);
    }

    template <typename iterator, typename Containers, size_t... Is>
    iterator end_impl(Containers& cs, std::index_sequence<Is...> ) {
        return iterator(end(std::get<Is>(cs))...);
    }
}

template <typename... Containers>
class  zipper
{
public:
    using iterator = detail::zip_iterator<decltype(begin(std::declval<Containers>()))...>;
    
    template <typename... T>
    zipper(T&&... ts)
        : cs(std::forward<T>(ts)...)
    {  }
    
    iterator begin() const {
        return detail::begin_impl<iterator>(cs, std::index_sequence_for<Containers...>{});
    }
    
    iterator end() const {
        return detail::end_impl<iterator>(cs, std::index_sequence_for<Containers...>{});
    }    

private:
    std::tuple<Containers...> cs;  
};

template <typename... Containers>
zipper<Containers...> zip(Containers&&... cs)
{
    return zipper<Containers...>(std::forward<Containers>(cs)...);
}

int main()
{
    std::vector<int> v{1, 2, 3};
    const std::map<char, long> m{{'a', 4}, {'b', 17}};
    
    for (auto tup : zip(v, m)) {
        ++std::get<0>(tup);
        //++std::get<1>(tup).second; // error: increment of member in read-only object
        std::cout << std::get<1>(tup).first << ' ';
    }
    std::cout << '\n';
    
    for (int i : v) {
        std::cout << i << ' ';
    }
    std::cout << '\n';
}