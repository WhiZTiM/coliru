#include <iostream>
#include <vector>

template<class Z> struct indexer{
    Z z;
    Z operator*()const{return z;}
    void operator++(){ ++z; }
    friend bool operator==(indexer lhs, indexer rhs){return lhs.z==rhs.z;}
    friend bool operator!=(indexer lhs, indexer rhs){return !(lhs==rhs);}
};
template<class Z> indexer<Z> index( Z z ) { return {std::move(z)}; }
struct nothing { template<class T> nothing(T&&){} };
template<class It, class S=nothing> struct range:
    S
{
    template<class C>
    range(C&& c, It s, It f):S(std::forward<C>(c)), b(s), e(f) {}
    range(It s, It f): b(s), e(f) {}
    It b; It e;
    It begin() const { return b; }
    It end() const { return e; }
};
template<class It> range<It> make_range( It b, It e ) { return {0, b, e}; }
template<class C, class It=decltype(std::begin(std::declval<C>()))>
std::enable_if_t<std::is_lvalue_reference<C>{}, range<It>> make_range( C&& c ) {
  return make_range( std::begin(c), std::end(c) );
}
template<class C, class It=decltype(std::begin(std::declval<C>()))>
std::enable_if_t<!std::is_lvalue_reference<C>{}, range<It, C>> make_range( C&& c ) {
  return { std::forward<C>(c), std::begin(c), std::end(c) };
}
    
template<class C> auto iterators_into( C&& c ) {
    using std::begin; using std::end;
    using It = decltype(index(begin(c)));
    using no_copy_needed = std::is_lvalue_reference<C>;
    using extra_storage = std::conditional_t< no_copy_needed{}, nothing, C >;
    
    return range< It, extra_storage >{ std::forward<C>(c), index(begin(c)), index(end(c))};
}

int main() {
    std::vector<int> v{1,2,3};
   
    for(auto it: iterators_into(v)) {
       ++*it;
       std::cout << *it;
    }
    std::cout << '\n';
    for(auto it: iterators_into(std::vector<int>{1,2,3})) {
       ++*it;
       std::cout << *it;
    }
    std::cout << '\n';
}