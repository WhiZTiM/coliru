#include <iterator>

template <typename Iter>
class Wrapper {
    Iter _cur;
    
    using _traits_type = std::iterator_traits<Iter>;
    
public:
    
    using iterator_type = Iter;
    using iterator_category = typename _traits_type::iterator_category;
    using value_type        = iterator_type;
    using difference_type   = typename _traits_type::difference_type;
    using pointer           = iterator_type*;
    using reference         = iterator_type&;
    
    iterator_type base() const { return _cur; }
    
    Wrapper() : _cur() {}
    
    explicit Wrapper(iterator_type i) : _cur(i) {}
    
    template <typename OtherIter>
    explicit Wrapper(Wrapper<OtherIter> const& i) : _cur(i.base()) {}

    iterator_type operator*() const {return _cur;}
    value_type const* operator->() const {return &_cur;}

    Wrapper& operator++() {++_cur; return *this;}
    Wrapper  operator++(int) {auto tmp = *this; ++*this; return tmp;}
    Wrapper& operator--() {--_cur; return *this;}
    Wrapper  operator--(int) {auto tmp = *this; --*this; return tmp;}
    
    Wrapper operator+(difference_type n) const {return {_cur + n};}
    Wrapper operator-(difference_type n) const {return {_cur - n};}
    
    Wrapper operator+=(difference_type n) const {return *this = *this + n;}
    Wrapper operator-=(difference_type n) const {return *this = *this - n;}
    
    iterator_type operator[](difference_type n) const { return _cur + n; }
};


template <typename I1, typename I2>
bool operator==( Wrapper<I1> const& lhs, Wrapper<I2> const& rhs)
{ return lhs.base() == rhs.base(); }
template <typename I1, typename I2>
bool operator!=( Wrapper<I1> const& lhs, Wrapper<I2> const& rhs)
{ return !(lhs == rhs); }
template <typename I1, typename I2>
bool operator<(Wrapper<I1> const& lhs, Wrapper<I2> const& rhs)
{ return lhs.base() < rhs.base(); }
template <typename I1, typename I2>
bool operator<=(Wrapper<I1> const& lhs, Wrapper<I2> const& rhs)
{ return !(rhs < lhs); }
template <typename I1, typename I2>
bool operator>(Wrapper<I1> const& lhs, Wrapper<I2> const& rhs)
{ return rhs < lhs; }
template <typename I1, typename I2>
bool operator>=(Wrapper<I1> const& lhs, Wrapper<I2> const& rhs)
{ return !(lhs < rhs); }

//! LWG #685
template <typename I1, typename I2>
auto operator-(Wrapper<I1> const& lhs, Wrapper<I2> const& rhs)
{ return lhs.base() - rhs.base(); }
template <typename I>
Wrapper<I> operator+(typename Wrapper<I>::difference_type n, Wrapper<I> const& lhs)
{ return lhs + n; }
template <typename I>
Wrapper<I> makeWrapper(I i)
{ return {i}; }

template <typename Iter>
struct IteratorPair {Iter first, last;};

template <typename Iter>
Iter begin(IteratorPair<Iter> const& pair) {return pair.first;}
template <typename Iter>
Iter   end(IteratorPair<Iter> const& pair) {return pair.last;}

template <typename Iter>
IteratorPair<Wrapper<Iter>> iters(Iter first, Iter last) {
    return {Wrapper<Iter>(first), Wrapper<Iter>(last)};
}

// ADL darf jemand anders einbauen. detail-namespace errichten, using-declarationen dort reinpasten, usw.
template <typename Range>
auto iters(Range& r) -> decltype(iters(std::begin(r), std::end(r))) {
    return iters(std::begin(r), std::end(r));
}

#include <vector>
#include <iostream>
 
int main()
{
    std::vector<int> v = { 1,2,3,4,5,6,7,8,9,10 };
    for ( auto it : iters(v) )
        std::cout << "Element: " << *it << std::endl; 
}