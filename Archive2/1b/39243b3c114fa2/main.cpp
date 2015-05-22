#include <vector>
#include <iostream>
#include <type_traits>
#include <tuple>
#include <typeinfo>
#include <initializer_list>
#include <functional>

 
  template<unsigned N>
  struct test 
  {
      template<class dim>
      static int get(dim & t)
      {
          return test<N-1>::get(t) * std::get<N>(t) ;
      }
     
  };
  
  template<>
  struct test<0>
  {
      template<class dim>
      static int get(dim & t)
      {
          return std::get<0>(t);
      }
  };
      
 template<class Buffer, class Extent >
  struct NDcontainer {} ;
  

  template<class Buffer, template <class... > class Extent , class... Sizes  >
  struct NDcontainer<Buffer, Extent<Sizes...> > : private Buffer
  {
     
    using type = typename Buffer::value_type ;    
    using Sizes_ = Extent<Sizes...>;
    using Buffer::push_back ;
    using Buffer::operator[] ;
    using Buffer::begin;
    using Buffer::end;
     
    Buffer data_ ;
    
    using dim = Extent<Sizes...>;
    
    dim size;
    
    template<typename... Ts>
    NDcontainer(Ts&...  args) 
    {
        data_.resize(sizeof...(args) );
        
        for(auto const& i : {args...})
        {
            data_.push_back(i) ; 
        }
    }
    
     void resize  (dim && t)
    {
     size = t ;
      data_.resize(test<sizeof...(Sizes)-1>::get(t));
    }
   
    //TODO
    NDcontainer(std::initializer_list<type> args ) : data_(args)
    {}
    
    constexpr static int rank() noexcept { return sizeof...(Sizes);   } 
     

  };
  
  
 
  
  template<class Buffer, class Extent>
  std::ostream& operator<< (std::ostream& os, NDcontainer<Buffer, Extent> & c )
  {
      for (auto const& elem : c.data_)
      {
          os << elem << " " ;
      }
      
      return os;
  }
  
  
  
int main()
{

  NDcontainer<std::vector<int> , std::tuple<int ,int>  > te {1,2};
  
  te.resize(std::make_tuple(10,10));

   // std::cout << te << std::endl ;
 //te.push_back(1);
 
 /*
 std::cout << te.rank() << std::endl;
 std::cout << te.data() << std::endl;
 std::cout << te[0] << std::endl;
 */
 
 return 0;
}