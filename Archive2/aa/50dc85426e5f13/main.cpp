#include <string>
#include <vector>
#include <iostream>
#include <utility>
#include <functional>
#include <sstream>

    template<class...Args>
    struct void_ptr_deferred_execution_t {
      std::tuple<Args&&...> args;
      void const* pf = nullptr;
      void_ptr_deferred_execution_t( std::tuple<Args&&...> a, void const* p ):
        args(std::move(a)),
        pf(p)
      {}
      template<class R, size_t...Is>
      R invoke( std::index_sequence<Is...> ){
        using f_t = R(*)(Args...);
        f_t f = f_t(pf);
        pf = nullptr;
        return f(std::forward<Args>(std::get<Is>(args))...);
      }
      template<class R>
      operator R()&&{
        return invoke<R>( std::index_sequence_for<Args...>{} );
      }
      ~void_ptr_deferred_execution_t() {
        if (pf) invoke<void>(std::index_sequence_for<Args...>{});
      }
    };
    
    class FunctionPointer
    {
      void* fp;
    public:
      FunctionPointer(void* ptr)
        : fp(ptr)
      {}

      template<class...Args>
      void_ptr_deferred_execution_t<Args...>
      operator()(Args&&...args)const {
        return { std::forward_as_tuple(std::forward<Args>(args)...), fp };
      }
    };
    
void hello(std::string msg){
    std::cout << "Hello " << msg << std::endl;
}

int main() {

    FunctionPointer f((void*)hello);

    std::function<void(std::string)> func_hello = f;

    func_hello("World!");

    return 0;
}
