#include <vector>
#include <iostream>
#include <type_traits>
#include <tuple>
#include <typeinfo>
#include <initializer_list>
#include <functional>
#include <array>


namespace tag {
    // shapes for NDcontainer
    struct shape_ {};
    struct dense_ : public shape_ {} ;
    struct diagonal_ : public shape_ {};
}


namespace option{
    // Specify matrix dimension size and size at compile time ?
    
    struct static_extent {};
    
    template<int... N>
    struct matrix : static_extent
    {
        static constexpr std::array<int,sizeof...(N)> value { {N...} }; 
        using type = std::array<int, sizeof...(N)>;    
    };   
}

template<class Container>
using is_diagonal = std::is_same<tag::diagonal_,typename Container::shape_>; 

template<int N>
using extent = std::array<unsigned int,N>;

template<int N0, int... N>
using extent_ = option::matrix<N0,N...> ;

/*
template <typename T, typename Tuple>
struct has_type;

template <typename T>
struct has_type<T, std::tuple<>> : std::false_type {};

template <typename T, typename U, typename... Ts>
struct has_type<T, std::tuple<U, Ts...>> : has_type<T, std::tuple<Ts...>> {};

template <typename T, typename... Ts>
struct has_type<T, std::tuple<T, Ts...>> : std::true_type {};
*/

template<class T, bool B>
struct get_extent_type ;

template<class T>
struct get_extent_type<T,true> {using type = typename T::type;};

template<class T>
struct get_extent_type<T,false> {using type = T;};

// Rework using predicate - finds if within options of NDcontainer we have a
// shape and returns it's index - use brigand 
template<int N, class Option, class... Params>
struct has_type_helper
{
  static constexpr auto get() noexcept
  {
    using type_ = typename std::tuple_element<N-1, std::tuple<Params...> >::type;
    return std::is_base_of<Option,type_ >::value ? N : has_type_helper<N-1,Params...,Option>::get()  ;
  }
};


template<class Option, class... Params>
struct has_type_helper<0,Option,Params...>
{
  static constexpr auto get() noexcept
  {
    return 0 ;
  }
};

template<int N, class Option, class... Params>
struct has_shape
{
    using type = typename std::tuple_element<has_type_helper<N-1,Params...,Option>::get() , std::tuple<Params...> >::type;
};

template<class Option, class... Params>
struct has_shape<0,Option,Params...>
{
    using type = tag::dense_;
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

// Acces dimensions from Variadic for operator()
template<unsigned int N, class dim>
struct unroll_dim
{
    inline static auto constexpr get(dim const& d)
    {
        return std::get<N-1>(d) * unroll_dim<N-1,dim>::get(d);
    }
};

template<class dim>
struct unroll_dim<0,dim>
{
    inline static auto constexpr get(dim const& )
    {
        return 1;
    }
};

template<unsigned int N, class dim, class... Indx>
struct get_idx
{
    inline static auto constexpr get(dim const& d, Indx... ind)
    {   
        return std::get<N-1>(std::make_tuple(ind...))*unroll_dim<N,dim>::get(d) + get_idx<N-1,dim,Indx...>::get(d,ind...);
    }
};

template<class dim, class... Indx>
struct get_idx<0,dim,Indx...>
{
    inline static auto constexpr get(dim const& , Indx...)
    {
        return 0;
    }
};

template <typename T, typename = int>
struct Has_ : std::false_type { };

template <typename T>
struct Has_ <T, decltype((void) T::x, 0)> : std::true_type { };


  template<class Buffer, class Extent, class ... Params>
struct NDcontainer : private Buffer
{

  using buffer_type = Buffer;
  using T = typename Buffer::value_type ;
  using reference = typename Buffer::reference;
  using const_reference = typename Buffer::const_reference;
  using Buffer::push_back ;
  using Buffer::operator[] ;
  using Buffer::data;
  using Buffer::begin;
  using Buffer::end;
  using Buffer::size;
  
  using static_size = typename std::is_base_of<option::static_extent,Extent>::type;
  using dim = typename get_extent_type<Extent,static_size::value>::type;
  using sz = std::tuple_size<dim>;
  
  using config_ = std::tuple<Params...>;  
  const static int config_size = sizeof...(Params);
  using shape_ = typename has_shape<config_size, tag::shape_, Params...>::type;
  
  dim sizes_ = init(static_size() ) ;

  NDcontainer() : sizes_(dim {} ) {}

  void resize  (dim const& t)
  {
    static_assert( !static_size::value , "statically initialized NDcontainer cannot be resized");
    sizes_ = t ;
    auto n = resize_helper<sz::value-1>::get(sizes_);
    Buffer::resize(n);
  }

  NDcontainer( dim const & d , std::initializer_list<T> args ) 
  {
    resize(d);
    std::copy(args.begin(),args.end(),Buffer::begin());
  }

  NDcontainer(std::initializer_list<T> args )
  {
    static_assert( static_size::value , "dimensions not specified");
    auto n = resize_helper<sz::value-1>::get(sizes_);
    Buffer::resize(n);
    std::copy(args.begin(),args.end(),Buffer::begin());
  }
  
  constexpr int rank()  const noexcept { return sz::value;}

  constexpr auto extent() const noexcept {return sizes_;}
  
  constexpr auto config() const noexcept {return config;}

  template<class... Indx>
  reference operator()(std::size_t const i,Indx... ind)  noexcept
  {
      static_assert(sizeof...(Indx) <= sz::value-1, "error too many dimensions");
      return *(this->data()+ i + get_idx<sizeof...(Indx),dim,Indx...>::get(sizes_,ind...));
  }

  template<class... Indx>
  const_reference operator()(std::size_t const i, Indx... ind) const noexcept
  {   
      static_assert(sizeof...(Indx) <= sz::value, "error too many dimensions");
      return *(this->data()+ i + get_idx<sizeof...(Indx),dim,Indx...>(sizes_));
  }

 private :
    constexpr auto init(std::integral_constant<bool,true> const ) noexcept
    {
        return Extent::value;
    }

    constexpr auto init(std::integral_constant<bool,false> const ) noexcept
    {
        return Extent {};
    }
};

template<int N, class buffer, class extent, class... params>
constexpr auto& get(NDcontainer<buffer,extent,params...> & c)
{
    return *(c.data() + N);
}

template<int N, class buffer, class extent, class... params>
constexpr const auto& get(NDcontainer<buffer,extent,params...> const& c)
{
    return *(c.data() + N);
}

template<int N, class buffer, class extent, class... params>
constexpr auto&& get(NDcontainer<buffer,extent,params...> && c)
{
    return *(c.data() + N);
}

template<class Container>
 auto height(Container const& c) 
{
    return std::get<0>(c.extent());
}


template<class Container>
 auto width(Container const& c) 
{
    return std::get<1>(c.extent());
}

 
 template<class Buffer, class Extent, class... Params>
std::ostream& operator<< (std::ostream& os, NDcontainer<Buffer, Extent, Params...> const& c )
{
  std::size_t i =1;
  for (auto const& elem : c)
  {
    os << elem << " " ;
    if( i++ % (width(c)) == 0 ) {os << "\n";}
  }
  return os;
}


/*
template<class Container1, class Container2, class... Params1, class... Params2 , typename std::enable_if<is_diagonal<NDcontainer<Container2,extent<2>,Params2...>>::value,int>::type = 0 >
auto dgemm(NDcontainer<Container1,extent<2>, Params1...> const& a, NDcontainer<Container2,extent<2>,Params2...> const& b )
{
  using shape = typename NDcontainer<Container1,extent<2>, Params1...>::shape_;
  NDcontainer<Container1 ,extent<2>, shape > c;
  std::cout<< "is diagonal\n";
  
  return c; 
}
*/

template<class Container1, class Container2, typename std::enable_if<is_diagonal<Container2>::value,int>::type = 0 >
auto dgemm(Container1 const& a, Container2 const& b )
{
  using Buffer = typename Container1::buffer_type;
  using Shape = typename Container1::shape_;
  NDcontainer< Buffer, extent<2>, Shape  > c;
  c.resize({3,3});
  std::cout<< "dgemm for A*D \n";
  
  return c; 
}



template<typename T,class... Params>
using mat = NDcontainer<std::vector<T>, extent<2>, Params...>;

template<typename T,class... Params>
using Dmat = NDcontainer<std::vector<T>, extent<2>, tag::diagonal_, Params...>;

int main()
{
  /* Test 1 : array init,tags, accesors, static dispatch,  */
  
  std::cout << "Test 1\n";
  
  NDcontainer<std::vector<int> , extent<2> > te({{3,3}}, {1,2,3,4,5,6,7,8,9});
 
  std::cout << te << std::endl;
  
  te(1,1) = 15;
  std::cout << "value : " << te(1,1) << std::endl;
  std::cout << "value : " << get<1>(te) << std::endl;
  
  //std::cout << te.size() << std::endl ;
  
  NDcontainer<std::vector<int> , extent<2>, tag::diagonal_ > te1({{2,2}}, {1,2,3,4});
  static_assert(std::is_same<NDcontainer<std::vector<int> , extent<2>, tag::diagonal_ >::shape_, tag::diagonal_>::value, "error");
  dgemm(te,te1);

  /* Test 2 :  */
  
  NDcontainer<std::vector<int> , extent_<3,3> > te2({1,2,3,4,5,6,7,8,9});
  
  std::cout << "Test 2 : " << te2.size() << std::endl;
  std::cout << te2 << std::endl;
  std::cout << std::is_same<NDcontainer<std::vector<int> , extent_<3,3> >::static_size , std::integral_constant<bool,true> >::value << std::endl; 
 
 
  return 0;
}

