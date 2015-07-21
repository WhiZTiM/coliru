#include <future>
#include <utility>
#include <type_traits>

struct Pixel8
{
   char r;
   char g;
   char b;
};
#define PIXEL8_MAX 255

template <class PIXEL>
auto getMax( ) -> decltype( PIXEL::r )
{
   static_assert( false, "getMax can only be called with a pixel type." );
}
template<>
auto getMax<Pixel8>( ) -> decltype( Pixel8::r )
{
   return PIXEL8_MAX;
}

int main()
{
    getMax<>();
    
}