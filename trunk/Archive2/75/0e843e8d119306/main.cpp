#include <tuple>
#include <utility>
#include <type_traits>

template<class S, class E>
struct unit_step {
    constexpr static bool exists = false;
};

struct Start {};
struct Point1 {};
struct Point2 {};
struct Point3 {};
struct End {};

#define CREATE_UNIT_STEP(S,E) template<> struct unit_step<S, E> { \
    constexpr static bool exists = true; \
}

CREATE_UNIT_STEP(Start, Point1);
CREATE_UNIT_STEP(Point1, Point2);
CREATE_UNIT_STEP(Point1, Point3);
CREATE_UNIT_STEP(Point2, End);
CREATE_UNIT_STEP(Point3, End);

template<class... Ts> struct type_list {
    template<size_t N>
    using get = std::tuple_element_t<N, std::tuple<Ts...>>;
    constexpr static std::size_t size = sizeof...(Ts);
    
    template<class T>
    constexpr static size_t index_of(){
        auto l = {std::is_same<T, Ts>::value...};
        size_t i = 0;
        for(auto b : l){
            if(b) return i;
            ++i;
        }
        return (size_t)-1;   
    }
    
    template<class... T1s>
    using append = type_list<Ts..., T1s...>;
};

template<class Seq, class>
struct repeat_impl;
    
template<size_t... Is, class T>
struct repeat_impl<std::index_sequence<Is...>, T>{
    template<size_t> using _ = T;
    using type = type_list<_<Is>...>;
};
    
template<class T, size_t N>
using make_repeat_list = typename repeat_impl<std::make_index_sequence<N>, T>::type;

struct None {};

template<class S, class E, class All, class Result, size_t N = All::template index_of<E>(),  bool has_path = !std::is_same<typename Result::template get<N>, None>::value>
struct do_result {
    // Current = current end of list
    template<class Current, bool = std::is_same<S, Current>::value>
    struct builder {
        constexpr static size_t I = All::template index_of<Current>();
        using prev = typename Result::template get<I>;
        using step_t = unit_step<prev, Current>;
        using type = typename builder<prev>::type::template append<step_t>;
    };
    template<class T>
    struct builder<T, true> { using type = type_list<>; };
    
    using type = typename builder<E>::type;
};

template<class S, class E, class All, class Result, size_t N>
struct do_result<S, E, All, Result, N, false> {
    // has no path
    using type = None;
};


// BFS
template<class S, class E, class All, class ToBeProcessed, class Result> struct BFS_impl;

template<class S, class E, class All, class Result>
struct BFS_impl<S, E, All, type_list<>, Result> : do_result<S, E, All, Result>{
};

template<class S, class E, class All, class Result, class T, class... Ts>
struct BFS_impl<S, E, All, type_list<T, Ts...>, Result> {
    template<class L, class N, class R, class A>
    struct add_reachable;
    
    template<class... T1s, class N, class R, class... AllT>
    struct add_reachable<type_list<T1s...>, N, R, type_list<AllT...>>{
        using type = type_list<std::conditional_t<unit_step<R, AllT>::exists && std::is_same<T1s, N>::value, R, T1s>...>;
    };
    
    using new_result = typename add_reachable<Result, None, T, All>::type;
    
    template<class OTBP, class OR, class NR, class A>
    struct compute_new_proc;
    template<class OTBP, class OR1, class NR1, class A1, class... ORs, class... NRs, class... As>
    struct compute_new_proc<OTBP, type_list<OR1, ORs...>, type_list<NR1, NRs...>, type_list<A1, As...>>
         : compute_new_proc<typename OTBP::template append<A1>, type_list<ORs...>, type_list<NRs...>, type_list<As...>> {};
    template<class OTBP, class R, class A1, class... ORs, class... NRs, class... As>
    struct compute_new_proc<OTBP, type_list<R, ORs...>, type_list<R, NRs...>, type_list<A1, As...>>
         : compute_new_proc<OTBP, type_list<ORs...>, type_list<NRs...>, type_list<As...>> {};
    template<class OTBP>
    struct compute_new_proc<OTBP, type_list<>, type_list<>, type_list<>> { using type = OTBP; };
    
    using new_proc = typename compute_new_proc<type_list<Ts...>, Result, new_result, All>::type;
        
    using type = typename BFS_impl<S, E, All, new_proc, new_result>::type;
};

template<class S, class E, class A>
using BFS = BFS_impl<S, E, A, type_list<S>, make_repeat_list<None, A::size>>;


using all_points = type_list<Start, Point1, Point2, Point3, End>;

template<class> class TD;
using T = BFS<Start, End, all_points>::type;

int main(){
    TD<T> t;
}
