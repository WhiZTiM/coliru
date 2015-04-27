#include <atomic>
#include <iostream>
#include <string>


template <typename T>
struct default_deleter
{
  void operator()( T * ptr )
  {
    delete ptr;
  }
};

template <typename T, typename Deleter = default_deleter<T>>
class just_shared_ptr
{
  T * raw_ptr;
  std::atomic<std::size_t> * counter;
public:
  just_shared_ptr( T * init ) : raw_ptr( init ), counter( new std::atomic<std::size_t>(1) ) {}

  T * operator->() const { return raw_ptr; }

  just_shared_ptr( const just_shared_ptr & other ) : raw_ptr( other.raw_ptr ), counter( other.counter )
  {
    ++( *counter );
  }

  T * get_raw() const { return raw_ptr; }

  just_shared_ptr & operator=( const just_shared_ptr & other )
  {
    raw_ptr =other.raw_ptr; counter =other.counter;
    ++( *counter );
    return *this;
  }

  ~just_shared_ptr()
  {
    if ( !--(*counter) )
    {
      Deleter()( raw_ptr );
      delete counter;
    }
  }
};

struct tracer_t
{
  std::string _name;

  tracer_t( const std::string & name ) : _name( name ) {std::cout << "created " << _name << std::endl;}
  ~tracer_t() {std::cout << "destroyed " << _name << std::endl;}
};

int main()
{
  just_shared_ptr<tracer_t> a ( new tracer_t("A") );
  just_shared_ptr<tracer_t> b ( new tracer_t("B") );

  a = b;

  return 0;
}