#include <iostream>
#include <functional>
#include <deque>

struct observable
{
    virtual ~observable() = default ;

    using observer = std::function< void( const observable& ) > ;

    template < typename CALLABLE > void attach( CALLABLE&& fn )
    { observers.emplace_back( std::forward<CALLABLE>(fn) ) ; }

    virtual void raise_event() { for( const observer& obs : observers ) obs(*this) ; }

    private: std::deque<observer> observers ;
};

void non_member_event_handler( const observable& source )
{ std::cout << "non_member_event_handler(sender:" << std::addressof(source) <<  ")\n" ; }

int main()
{
    observable subject ;

    struct an_observer
    {
        explicit an_observer( observable& obs )
        { obs.attach( std::bind( &an_observer::on_event, this, std::placeholders::_1 ) ) ; }
        // on_event is private; a member of the class can still access it.

        private:
            void on_event( const observable& source ) const
            { std::cout << "an_observer::on_event(sender:" << std::addressof(source) <<  ")\n" ; }
    };

    an_observer observer(subject) ;
    subject.attach( []( const observable& source )
                    { std::cout << "closure(sender:" << std::addressof(source) <<  ")\n" ; } ) ;

    subject.raise_event() ;
    std::cout << "------------\n" ;

    subject.attach(non_member_event_handler) ;

    struct function_object
    {
        void operator() ( const observable& source ) const
        { std::cout << "function_object::operator()(sender:" << std::addressof(source) <<  ")\n" ; }
    };
    subject.attach( function_object{} ) ;

    subject.raise_event() ;
}
