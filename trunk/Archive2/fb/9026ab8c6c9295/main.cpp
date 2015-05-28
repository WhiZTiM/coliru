    #include <algorithm>
    using std::is_sorted;
    using std::iota;

    #include <assert.h>

    #include <iterator>
    using std::reverse_iterator;

    #include <iostream>
    using std::ostream; using std::cout; using std::endl;

    #include <utility>
    using std::begin; using std::end;

    #include <vector>
    using std::vector;

    #include <set>
    using std::multiset;

    template< class Container, class Enable_if = typename Container::value_type >
    auto operator<<( ostream& stream, const Container& c )
        -> ostream&
    {
        stream << "{";
        int n_items_outputted = 0;
        for( const int x : c )
        {
            if( n_items_outputted >= 1 ) { stream << ", "; }
            stream << x;
            ++n_items_outputted;
        }
        stream << "}";
        return stream;
    }

    template< class It >
    auto ascend_ordered( const int n_digits, const It begin, const It end )
        -> bool
    {
        using R_it = reverse_iterator< It >;
        const R_it r_begin  = R_it( end );
        const R_it r_end    = R_it( begin );

        int max_digit = n_digits - 1;
        for( R_it it = r_begin ; it != r_end; ++it )
        {
            if( *it < max_digit )
            {
                ++*it;
                const int n_further_items = it - r_begin;
                for( It it2 = end - n_further_items; it2 != end; ++it2 )
                {
                    *it2 = *(it2 - 1) + 1;
                }
                return true;
            }
            --max_digit;
        }
        return false;
    }

    auto main() -> int
    {
        vector<int> a = {1,2,2,3,3,3,3};
        assert( is_sorted( begin( a ), end( a ) ) );
        const int k = 2;
        const int n = a.size();
        vector<int> indices( k );
        iota( indices.begin(), indices.end(), 0 );      // Fill with 0, 1, 2 ...
        multiset<int> previous;
        for( ;; )
        {
            multiset<int> current;
            for( int const i : indices ) { current.insert( a[i] ); }
            if( current != previous )
            {
                cout << "Indices " << indices << " -> values " << current << endl;
            }
            if( not ascend_ordered( n, begin( indices ), end( indices ) ) )
            {
                break;
            }
            previous = current;
        }
    }
