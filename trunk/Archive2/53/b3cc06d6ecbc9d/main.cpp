#include <tuple>
#include <utility>
#include <stddef.h>

template<typename...> class type_pack;

template<typename...> class MethodHelper;

template<typename ... ReturnTypes, typename ... ArgTypes>
class MethodHelper<type_pack<ReturnTypes...>, type_pack<ArgTypes...>>{
    public:
        static_assert(
            sizeof...(ReturnTypes) == sizeof...(ArgTypes),
            "number of return types not the same as argument types"
        );

        static auto Method(ArgTypes &&... args){
            return std::tuple<ReturnTypes...>(std::forward<ArgTypes>(args)...);
        }
};

template<typename ReturnPack, typename ArgsPack, typename ... Args>
auto Method(Args &&... args){
    return MethodHelper<ReturnPack, ArgsPack>::Method(std::forward<Args>(args)...);
}

auto main() -> int{
    size_t a = 5, b = 6;
    auto t = Method<type_pack<size_t, size_t>, type_pack<size_t, size_t>>(a, b);
    
    (void)t;
}
