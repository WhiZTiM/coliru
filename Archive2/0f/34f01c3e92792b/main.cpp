#include <iostream>
#include <fstream>
#include <fstream>
#include <vector>
#include <type_traits>

struct A // MoveConstructible, MoveAssignable, not CopyConstructible, not CopyAssignable
{
    explicit A( std::string path ) : file(path) {}
    A( std::ofstream&& stm ) : file( std::move(stm) ) {} // transfer ownership of the stream

    void test_it() { file << "output from A #" << id << '\n' ; }

    std::ofstream file ; // std::ofstream is Moveable, but it is not Copyable
    // copy constructor of A is implicitly deleted
    // move constructor of A is implicitly defaulted
    // copy assignment of A is implicitly deleted
    // move assignment of A is implicitly defaulted

    int id = ++seq_no ;
    static int seq_no ;
};

int A::seq_no = 0 ;

int main()
{
    std::cout << std::boolalpha
              << "MoveConstructible? " << std::is_move_constructible<A>::value << '\n'
              << "CopyConstructible? " << std::is_copy_constructible<A>::value << '\n'
              << "MoveAssignable? " << std::is_move_assignable<A>::value << '\n'
              << "CopyAssignable? " << std::is_copy_assignable<A>::value << '\n' ;

    std::vector<A> seq ;

    seq.emplace_back( "out0.txt" ) ;
    seq.push_back( std::ofstream( "out1.txt" ) );

    std::ofstream file( "out2.txt" ) ;
    seq.emplace_back( std::move(file) ) ;
    
    for( A& a : seq ) a.test_it() ;

    A object( "out3.txt" ) ;
    
    // seq.push_back( object ); // *** error: call to implicitly-deleted copy constructor of 'A'
                                //      note: ... implicitly deleted because field 'file' has a deleted copy constructor
    
    seq.push_back( std::move(object) ); // MoveConstructible
    seq.back().test_it() ;

    seq.back() = A( "out4.txt" ) ; // MoveAssignable
    seq.back().test_it() ;

    A object2( "out5.txt" ) ;
    
    // seq.front() = object2 ; // *** error: ... copy assignment operator is implicitly deleted 
                               //      note: ... implicitly deleted because field 'file' has a deleted copy assignment operator
                            
    seq.front() = std::move(object2) ; // MoveAssignable
    seq.front().test_it() ;

    using std::swap ;
    swap( seq.front(), seq.back() ) ; // Moveable
    for( A& a : seq ) a.test_it() ;
}
