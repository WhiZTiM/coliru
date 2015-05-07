#include <iostream>
#include <vector>
#include <algorithm>
#include <memory>

/*struct FlagNth
{
  FlagNth( size_t n ) : current_( 0 ), n_( n ) {}

  FlagNth( const FlagNth& other ) :
    current_( other.current_ ),
    n_( other.n_ )
  {
    std::cout << "copy ctor is called" << std::endl;
    ++count_copy;
  }

  FlagNth& operator=( const FlagNth& other )
  {
    current_ = other.current_;
    n_ = other.n_;
    std::cout << "copy assing is called" << std::endl;
    ++count_copy;
    return *this;
  }

  template < class T >
  bool operator()( const T& ) { return ++current_ == n_; }

  static size_t count_copy;

private:
  size_t current_;
  size_t n_;
};

size_t FlagNth::count_copy = 0;*/

struct FlagNthImpl
{
  FlagNthImpl( size_t n ) : current_( 0 ), n_( n ) {}
  size_t current_;
  size_t n_;
};

struct FlagNth
{
  FlagNth( size_t n ) : pimpl_( new FlagNthImpl( n ) ) {}

  FlagNth( const FlagNth& other ) :
    pimpl_( other.pimpl_ )
  {
    std::cout << "copy ctor is called" << std::endl;
    ++count_copy;
  }

  FlagNth& operator=( const FlagNth& other )
  {
    pimpl_ = other.pimpl_;
    std::cout << "copy assing is called" << std::endl;
    ++count_copy;
    return *this;
  }

  template < class T >
  bool operator()( const T& ) { return ++( pimpl_->current_ ) == pimpl_->n_; }

  static size_t count_copy;

private:
  std::shared_ptr< FlagNthImpl > pimpl_;
};

size_t FlagNth::count_copy = 0;

template < class Cont >
void show( const Cont& cont )
{
  std::for_each( std::begin( cont ), std::end( cont ),
    []( const typename Cont::value_type& e ) { std::cout << e << ' '; } );

  std::cout << std::endl;
}

int main()
{
  int init[] = { 1, 2, 3, 4, 5 };
  std::vector< int > v( init, init + 5 );

  v.erase( std::remove_if( v.begin(), v.end(), FlagNth( 1 ) ), v.end() );
  std::cout << "count_copy: " << FlagNth::count_copy << std::endl;
  show( v );

  std::cin.get();
  return 0;
}