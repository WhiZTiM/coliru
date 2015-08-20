#include <string>
#include <vector>
#include <iostream>
#include <utility>
#include <functional>
#include <sstream>
#include <type_traits>
#include <memory>

    template<class Sig, size_t sz, size_t algn>
    struct small_task;

    template<class R, class...Args, size_t sz, size_t algn>
    struct small_task<R(Args...), sz, algn>{
      struct vtable_t {
        void(*mover)(void* src, void* dest);
        void(*destroyer)(void*);
        R(*invoke)(void const* t, Args&&...args);
        template<class T>
        static vtable_t const* get() {
          static const vtable_t table = {
            [](void* src, void*dest) {
              new(dest) T(std::move(*static_cast<T*>(src)));
            },
            [](void* t){ static_cast<T*>(t)->~T(); },
            [](void const* t, Args&&...args)->R {
              return (*static_cast<T const*>(t))(std::forward<Args>(args)...);
            }
          };
          return &table;
        }
      };
      vtable_t const* table = nullptr;
      std::aligned_storage_t<sz, algn> data;
      template<class F,
        class dF=std::decay_t<F>,
        std::enable_if_t<!std::is_same<dF, small_task>{}>* = nullptr,
        std::enable_if_t<std::is_convertible< std::result_of_t<dF&(Args...)>, R >{}>* = nullptr
      >
      small_task( F&& f ):
        table( vtable_t::template get<dF>() )
      {
        static_assert( sizeof(dF) <= sz, "object too large" );
        static_assert( alignof(dF) <= algn, "object too aligned" );
        new(&data) dF(std::forward<F>(f));
      }
      ~small_task() {
        if (table)
          table->destroyer(&data);
      }
      small_task(small_task&& o):
        table(o.table)
      {
        if (table)
          table->mover(&o.data, &data);
      }
      small_task(){}
      small_task& operator=(small_task&& o){
        this->~small_task();
        new(this) small_task( std::move(o) );
        return *this;
      }
      explicit operator bool()const{return table;}
      R operator()(Args...args)const{
        return table->invoke(&data, std::forward<Args>(args)...);
      }
    };
    
    template<class Sig>
    using task = small_task<Sig, sizeof(void*)*4, alignof(void*) >;
    
    
    int main() {
        task<void()> t = []{ std::cout << "hello world\n"; };
        t();
        #if 0 // the below fails:
        std::array<int, 100> buffer{1,2,3,4,5,6};
        t = [buffer]{
            for (int x:buffer) std::cout << x << '\n';
        };
        #endif
    }
