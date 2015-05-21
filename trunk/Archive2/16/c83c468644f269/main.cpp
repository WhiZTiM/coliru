#include <iostream>
#include <memory>

template< typename T > struct fwd_list
{
    struct node
    {
        node( const T& v, std::unique_ptr<node>&& n = nullptr ) : value(v), next( std::move(n) )
        { ++constructor_cnt ; }

        ~node() { ++destructor_cnt ; }

        ////////////////////////
        node( node&& ) = delete ;
        ///////////////////////

        T value ;
        std::unique_ptr<node> next ;

        static int constructor_cnt ;
        static int destructor_cnt ;
    };

    std::unique_ptr<node> head ;
    node* tail = nullptr ;

    template < typename U > void add( U&& v )
    {
        if( tail != nullptr )
        {
            tail->next = std::make_unique<node>( std::forward<U>(v) ) ;
            tail = tail->next.get() ;
        }
        else
        {
            head = std::make_unique<node>( std::forward<U>(v) ) ;
            tail = head.get() ;
        }
    }

    void erase( const T& v )
    {
        if( head == nullptr ) return ;

        node* prev = head.get() ;
        node* curr = prev ;

        while( curr != nullptr )
        {
            if( curr->value == v ) break ;
            prev = curr ;
            curr = curr->next.get() ;
        }

        if( curr == tail ) { tail = prev ; tail->next = nullptr ; }
        if( curr == head.get() ) head = std::move( head->next ) ;
        else if(prev) prev->next = prev->next ? std::move( prev->next->next ) : nullptr ;
    }

    std::ostream& print( std::ostream& stm = std::cout ) const
    {
        stm << "[ " ;
        for( node* n = head.get() ; n != nullptr ; n = n->next.get() )
            stm << n->value << ' ' ;
        return stm << "]  (constructor/destructor counts: " << node::constructor_cnt
                   << '/' << node::destructor_cnt << ")\n\n" ;

    }
};

template< typename T > int fwd_list<T>::node::constructor_cnt = 0 ;
template< typename T > int fwd_list<T>::node::destructor_cnt = 0 ;

int main()
{
   {
        //initalize
        fwd_list<int> lst;

        //add values
        for( int v = 1 ; v < 6 ; ++v ) lst.add(v);
        lst.print();

        //add and delete
        std::cout<<"deleting first value: ";
        lst.erase(1);
        lst.print();

        std::cout<<"deleting third value: ";
        lst.erase(3);
        lst.print();

        std::cout<<"adding new value: 6 "; //<<endl;
        lst.add(6);
        lst.print();

        std::cout<<"deleting last value: ";
        lst.erase(6);
        lst.print();
   }

   std::cout << "final constructor/destructor counts: "
             << fwd_list<int>::node::constructor_cnt
             << '/' << fwd_list<int>::node::destructor_cnt << '\n' ;
}
