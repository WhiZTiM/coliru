#include <iostream>
#include <vector>
#include <queue>
#include <functional>
#include <string>

template < typename T > std::priority_queue< T, std::vector<T>, std::greater<> > min_heap {} ;

int main()
{
    auto& mhi = min_heap<int> ;
    auto& mhs = min_heap<std::string> ;

    for( int v : { 22, 56, 12, 98, 72, 18, 56, 82, 10, 75 } ) mhi.push(v) ;
    for( std::string s : { "abc", "xyz", "efgh", "mnop", "aaaaa" } ) min_heap<std::string>.push(s) ;

    std::cout << min_heap<int>.size() << ' ' << mhs.size() << '\n' ; // 10 5

    while( !mhi.empty() ) { std::cout << mhi.top() << ' ' ; mhi.pop() ; }
    std::cout << '\n' ;

    while( !mhs.empty() ) { std::cout << mhs.top() << ' ' ; mhs.pop() ; }
    std::cout << '\n' ;
}
