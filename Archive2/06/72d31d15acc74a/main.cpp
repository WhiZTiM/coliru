#include <vector>
#include <iostream>
#include <type_traits>
#include <tuple>
#include <typeinfo>
#include <initializer_list>
#include <functional>
#include <array>

  template<unsigned N>
  struct resize_helper
  {
      template<class dim>
      static int get(dim const& t)
      {
          return resize_helper<N-1>::get(t) * std::get<N>(t) ;
      }

  };

  template<>
  struct resize_helper<0>
  {
      template<class dim>
      static int get(dim const& t)
      {
          return std::get<0>(t);
      }
  };
 


  template<class Buffer, class Extent, class ... Params>
  struct NDcontainer : private Buffer
  {

    using type = typename Buffer::value_type ;
    using Buffer::push_back ;
    using Buffer::operator[] ;
    using Buffer::begin;
    using Buffer::end;
    using Buffer::size;
    
    using dim = Extent;
    
    using sz = std::tuple_size<dim>;
    using config_ = std::tuple<Params...>;
    
    dim sizes_ ;

    NDcontainer() : sizes_(dim {} ) {}

    void resize  (dim const & t)
    {
      sizes_ = t ;
      auto n = resize_helper<sz::value-1>::get(sizes_);
      Buffer::resize(n);
    }

    NDcontainer( dim const & d , std::initializer_list<type> args )
    {
        resize(d);
        std::copy(args.begin(),args.end(),Buffer::begin());
    }

    constexpr static int rank() noexcept { return sz::value;   }

    constexpr auto extent() noexcept {return sizes_;}
    
    constexpr auto config() noexcept {return config;}


  };

  template<class Buffer, class Extent>
  std::ostream& operator<< (std::ostream& os, NDcontainer<Buffer, Extent> & c )
  {
      for (auto const& elem : c)
      {
          os << elem << " " ;
      }

      return os;
  }


template<int N>
using extent = std::array<int,N>;

template<class Container>
using array2D = NDcontainer<Container , extent<2> >;

template<class Container1, class Container2, class... Params1, class... Params2>
auto dgemm(NDcontainer<Container1,extent<2>, Params1...> const& a, NDcontainer<Container2,extent<2>,Params2...> const& b)
{
    NDcontainer<Container1 ,extent<2>, Params1... > c;
    
    
    
    return c; 
}




template<class Container1, class Container2, class... Params1, class... Params2>
auto dgemm(NDcontainer<Container1,extent<2>, Params1...> const& a, NDcontainer<Container2,extent<2>,Params2...> const& b, std::enable_if<>)
{
    NDcontainer<Container1 ,extent<2>, Params1... > c;
    
    
    
    return c; 
}


int main()
{
  NDcontainer<std::vector<int> , extent<2> > te({{2,2}}, {1,2,3,4});
  
  std::cout << te.size() << std::endl ;

  std::cout << te << std::endl ;

  te.resize({4,4});

  std::cout << te.size() << std::endl ;
  std::cout << te << std::endl ;

 return 0;
}
