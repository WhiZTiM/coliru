#include <iostream>
#include <vector>

template<class Z> struct indexer{ Z z; Z operator*()const{return z;} void operator++(){ ++z; } friend bool operator==(indexer lhs, indexer rhs){return lhs.z==rhs.z;} friend bool operator!=(indexer lhs, indexer rhs){return !(lhs==rhs);}};
template<class Z> indexer<Z> index( Z z ) { return {std::move(z)}; }
template<class It> struct range{ It b; It e; It begin() const { return b; } It end() const { return e; } };
template<class It> range<It> make_range( It b, It e ) { return {b,e}; }
template<class C> auto iterators_into( C&& c ) { using std::begin; using std::end; return make_range( index(begin(c)), index(end(c)) ); }

int main() {
    std::vector<int> v{1,2,3};
   
    for(auto it: iterators_into(v)) {
       std::cout << *it;
    }
    std::cout << '\n';
}