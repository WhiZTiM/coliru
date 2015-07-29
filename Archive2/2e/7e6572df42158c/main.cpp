#include <vector>
#include <iostream>
#include <type_traits>
#include <tuple>
#include <typeinfo>
#include <initializer_list>
#include <functional>
#include <array>


struct shape_ {};
struct dense_ : public shape_ {} ;
struct diagonal_ : public shape_ {};

    template<class T>
struct shape_helper {using type = T;};

template <typename T, typename Tuple>
struct has_type;

template <typename T>
struct has_type<T, std::tuple<>> : std::false_type {};

template <typename T, typename U, typename... Ts>
struct has_type<T, std::tuple<U, Ts...>> : has_type<T, std::tuple<Ts...>> {};

template <typename T, typename... Ts>
struct has_type<T, std::tuple<T, Ts...>> : std::true_type {};

template<class Tuple>
using is_diagonal =  typename has_type<diagonal_,Tuple>::type;

template<int N, class... Params>
struct has_shape_helper
{
  static constexpr auto get()
  {
    using type_ = typename std::tuple_element<N-1, std::tuple<Params...> >::type;
    return std::is_base_of<shape_,type_ >::value ? N : has_shape_helper<N-1,Params...>::get()  ;
  }
};


template<class... Params>
struct has_shape_helper<0,Params...>
{
  static constexpr auto get()
  {
    return 0 ;
  }
};

template<int N, class... Params>
struct has_shape
{
    using type = typename std::tuple_element<has_shape_helper<N-1,Params...>::get() , std::tuple<Params...> >::type;
};

template<class... Params>
struct has_shape<0,Params...>
{
    using type = dense_;
};

/*
template<int N, class... Params>
constexpr auto has_shape()
{
  return typename std::tuple_element<has_shape_helper<N,Params...>::get() , std::tuple<Params...> >::type {};
}
*/


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
  const static int config_size = sizeof...(Params);
  using shape_ = typename has_shape<config_size, Params...>::type;
  
  
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


template<class Container1, class Container2, class... Params1, class... Params2 , typename std::enable_if<is_diagonal<std::tuple<Params2...>>::value,int>::type = 0 >
auto dgemm(NDcontainer<Container1,extent<2>, Params1...> const& a, NDcontainer<Container2,extent<2>,Params2...> const& b )
{
  NDcontainer<Container1 ,extent<2>, Params1... > c;
  //has_shape<config_size, Params...>::type;
  std::cout<< "is diagonal\n";
  
  return c; 
}


using t_ = std::tuple_element<0, std::tuple<diagonal_>>::type;

int main()
{
  NDcontainer<std::vector<int> , extent<2> > te({{2,2}}, {1,2,3,4});
  NDcontainer<std::vector<int> , extent<2>, diagonal_ > te1({{2,2}}, {1,2,3,4});
  
  std::cout << te.size() << std::endl ;

  std::cout << te << std::endl ;

  te.resize({4,4});

  std::cout << te.size() << std::endl ;
  std::cout << te << std::endl ;
  
  std::cout << "config_size :" << te1.config_size << std::endl;
  
  static_assert( te1.config_size == 1 , "error");
  
 // std::cout << t_{} << std::endl;
  std::cout << te1.shape_{} << std::endl;
  
  dgemm(te,te1);

  return 0;
}

