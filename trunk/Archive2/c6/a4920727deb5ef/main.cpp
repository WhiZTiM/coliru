#include <iostream>
#include <functional>
#include <tuple>
#include <vector>
#include <type_traits>


// clang++-3.5 -v -stdlib=libc++ -std=c++14 -O2 -Wall -pedantic -pthread t.cpp && ./a.out

//=======================================

template<unsigned...> struct index_tuple{};

template<unsigned I, typename IndexTuple, typename... Types>
struct make_indices_impl;

template<unsigned I, unsigned... Indices, typename T, typename... Types>
struct make_indices_impl<I, index_tuple<Indices...>, T, Types...>
{
  typedef typename 
    make_indices_impl<I + 1, 
                      index_tuple<Indices..., I>, 
                      Types...>::type type;
};

template<unsigned I, unsigned... Indices>
struct make_indices_impl<I, index_tuple<Indices...> >
{
  typedef index_tuple<Indices...> type;
};

template<typename... Types>
struct make_indices 
  : make_indices_impl<0, index_tuple<>, Types...>
{};


template <unsigned... Indices, class... Args, class CbT>
void forward_impl(index_tuple<Indices...>,
                 std::tuple<Args...> tuple,
                 CbT fptr)
{
  fptr(std::get<Indices>(tuple)...);
}

template<class... Args, class CbT>
void forward(std::tuple<Args...> tuple, CbT fptr)
{
typedef typename make_indices<Args...>::type Indices;    
   return forward_impl(Indices(), tuple, fptr);
}


template <typename... A>
struct EventPkg
{   
  using CBT = std::function<void(A...)>;
  using ArgTup = std::tuple<A...>;
  ArgTup argsSave;    

  void load(A&&... args)
  {       
      argsSave = std::make_tuple(std::forward<A>(args)...);
  }

};


template<typename T, typename CBT, typename... Args>
decltype(auto) waitEvt2(std::tuple<T>ap, CBT cb, Args... args) {
  std::cout << "Call2 " << " ---->" << __PRETTY_FUNCTION__ << "\n";
  forward(ap, cb);
  waitEvt(args...);
}

template<typename T, typename... Args>
decltype(auto) waitEvt(EventPkg<T> t, Args... args) {
  std::cout << "Call1 "<< " ---->"  <<  __PRETTY_FUNCTION__ << "\n";
  using EvtType = EventPkg<T>;
  typename EvtType::ArgTup cbArgs = t.argsSave;
  return waitEvt2(cbArgs, args...);
}

EventPkg<int> evt1;
EventPkg<int, int> evt2;

int main() {
  std::cout << "\n===================\n";
  evt1.load(99);
  evt2.load(1000, 2000);
  waitEvt(
    evt1, [](int x){
      std::cout << "evt1 " << x << "\n";
    }, 
    evt2, [](int x, int y){
      std::cout << "evt2 " << x << " " << y << "\n";
    }
  );
  std::cout << "\n\n";
    
}