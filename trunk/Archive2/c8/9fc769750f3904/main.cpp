    #include <utility>
    #include <type_traits>
    #include <memory>
    
    template<class Sig>
    struct function_view;
    
    template<class R, class...Args>
    struct function_view<R(Args...)>{
      void* state;
      R(*f)(void*, Args&&...);
      
      template<class F, class=std::enable_if_t<std::is_convertible<std::result_of_t<F&(Args...)>,R>{}>>
      function_view( F&& fin ):
        state(const_cast<void*>(static_cast<void*>(std::addressof(fin)))),
        f( [](void* state, Args&&...args)->R{
          F&& f = std::forward<F>(*static_cast<std::decay_t<F>*>(state));
          return f(std::forward<Args>(args)...);
        })
      {}
      function_view( R(*fin)(Args...) ):
        state(fin),
        f( fin?+[](void* state, Args&&...args)->R{
          R(*f)(Args...) = static_cast<R(*)(Args...)>(state);
          return f(std::forward<Args>(args)...);
        }:nullptr)
      {}
      explicit operator bool(){return f;}
      function_view():state(nullptr),f(nullptr){}
      function_view(std::nullptr_t):function_view(){}
      R operator()(Args...args)const{
        return f(state, std::forward<Args>(args)...);
      }
    };
    template<class...Args>
    struct function_view<void(Args...)>{
      void* state;
      void(*f)(void*, Args&&...);
      
      template<class F, class=std::result_of_t<F&(Args...)>>
      function_view( F&& fin ):
        state(const_cast<void*>(static_cast<void*>(std::addressof(fin)))),
        f( [](void* state, Args&&...args){
          F&& f = std::forward<F>(*static_cast<std::decay_t<F>*>(state));
          f(std::forward<Args>(args)...);
        })
      {}
      function_view( void(*fin)(Args...) ):
        state(fin),
        f( fin?+[](void* state, Args&&...args){
          void(*f)(Args...) = static_cast<void(*)(Args...)>(state);
          f(std::forward<Args>(args)...);
        }:nullptr)
      {}
      
      explicit operator bool(){return f;}
      function_view():state(nullptr),f(nullptr){}
      function_view(std::nullptr_t):function_view(){}
      void operator()(Args...args)const{
        f(state, std::forward<Args>(args)...);
      }
    };
    
    int main() {
      auto f2 = [] (function_view<void()> x=[]{}) {
        x();
      };
      //f1();
      f2();
      //[](auto x=0){}();
    }
    
