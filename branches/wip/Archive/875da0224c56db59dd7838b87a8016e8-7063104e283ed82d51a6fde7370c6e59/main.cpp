#include <iostream>
#include <tuple>
#include <utility>
#include <type_traits>
#include <functional>
#include <vector>

struct to_t { };
const auto to = to_t();

struct until_t { };
const auto until = until_t();

template <typename T>
struct set_build {
    std::vector<T> items;
    
    set_build () {
        
    }
    
    set_build ( std::vector<T> build ) : items(std::move(build)) {
        
    }
    
    typename std::vector<T>::iterator begin () {
        return std::begin( items );
    }
    
    typename std::vector<T>::iterator end () {
        return std::end( items );
    }
    
    typename std::vector<T>::const_iterator begin () const {
        return std::begin( items );
    }
    
    typename std::vector<T>::const_iterator end () const {
        return std::end( items );
    }

    template <typename TFx>
    set_build<T> operator% ( TFx&& fx ) {
        std::vector<T> filtered;
        filtered.reserve( items.size() );
        for ( auto&& item : items ) {
            if ( fx( item ) )
                filtered.emplace_back( item );
        }
        items = std::move( filtered );
        return *this;
    }
    
};

template <typename TFx, typename T>
set_build<T> operator| ( TFx&& fx, const set_build<T>& set ) {
    std::vector<T> comprehension;
    comprehension.reserve( set.items.size() );
    for ( auto& item : set ) {
       comprehension.emplace_back( fx( item ) );
    }
    return set_build<T>( std::move( comprehension ) );
}

template <typename T, typename T0, typename T1 = T0, typename TDiff = decltype( std::declval<T1>() - std::declval<T0>() )>
set_build<T> make_specific ( T0&& n0, const to_t&, T1&& n1, TDiff&& ndiff = static_cast<TDiff>(1) ) {
    std::vector<T> items;
    if ( n0 == n1 || ndiff == static_cast<TDiff>( 0 ) )
        return set_build<T>( std::move( items ) );
    
    T c0 = n0;
    
    if ( n0 < n1 ) {
        if ( ndiff < static_cast<TDiff>( 0 ) )
            return set_build<T>( std::move( items ) );
        
        while ( c0 <= n1 ) {
            items.emplace_back( c0 );
            c0 += ndiff;
        }
    }
    else {
        if ( ndiff > static_cast<TDiff>( 0 ) )
            return set_build<T>( std::move( items ) );
        
        while ( c0 >= n1 ) {
            items.emplace_back( c0 );
            c0 += ndiff;
        }
    }
    
    return set_build<T>( std::move( items ) );
}

template <typename T0, typename T1 = T0>
set_build<T0> make ( T0&& n0, T1&& n1 ) {
    return make_specific<T0, T0, T1>( std::forward<T0>( n0 ), to, std::forward<T1>( n1 ) ); 
}

template <typename T0, typename T1 = T0, typename TDiff = decltype( std::declval<T1>() - std::declval<T0>() )>
set_build<T0> make ( T0&& n0, const to_t&, T1&& n1, TDiff&& ndiff = static_cast<TDiff>(1) ) {
    return make_specific<T0, T0, T1, TDiff>( std::forward<T0>( n0 ), to, std::forward<T1>( n1 ), std::forward<TDiff>( ndiff ) ); 
}

template <typename T, typename T0, typename T1 = T0, typename TLim = T0>
set_build<T> make_specific ( T0&& n0, T1&& n1, const until_t&, TLim&& nlim ) {
    typedef decltype( std::declval<T1>() - std::declval<T0>() ) TDiff;
    TDiff ndiff = n1 - n0;
    return make_specific<T, T0, TLim, TDiff>( std::forward<T0>( n0 ), to, std::forward<TLim>( nlim ), std::forward<TDiff>( ndiff ) );
}

template <typename T0, typename T1 = T0, typename TLim = T0>
set_build<T0> make ( T0&& n0, T1&& n1, const until_t&, TLim&& nlim ) {
    return make_specific<T0, T0, T1, TLim>( std::forward<T0>( n0 ), std::forward<T1>( n1 ), until, std::forward<TLim>( nlim ) ); 
}

template <typename T0, typename T1 = T0, typename TLim = T0>
set_build<T0> make ( T0&& n0, T1&& n1, TLim&& nlim ) {
    return make_specific<T0, T0, T1, TLim>( std::forward<T0>( n0 ), std::forward<T1>( n1 ), until, std::forward<TLim>( nlim ) ); 
}

template <typename TRange>
void Print ( TRange&& range ) {
    std::cout << "[ ";
    for ( auto& r : range ) {
        std::cout << r << ' ';
    }
    std::cout << "]" << std::endl;
}

int main ( int argc, char** argv ) {
    // While the next line would be the ideal math-like syntax
    // we can't have it because `operator|` is left-associative
    //auto results = [ ( x * x ) | (1, 20) | (x * x > 144) ] ;
    // So, we'll use a different operator for filtering (&) and another for range operations (|)
    auto results1 = []( int x ) { return x * x; } | make( 1, to, 20 ) % []( int x ){ return x * x > 144; };
    std::cout << "make(1, to, 20):" << std::endl;
    Print( results1 );
    
    auto results2 = []( int x ) { return x * x; } | make( 1, 2, 20 ) % []( int x ){ return x * x > 144; };
    std::cout << "make(1, 2, 20):" << std::endl;
    Print( results2 );
    
    auto results3 = []( int x ) { return x * x; } | make( 0, 2, 20 ) % []( int x ){ return x * x > 144; };
    std::cout << "make(1, 4, 20):" << std::endl;
    Print( results3 );
    
}