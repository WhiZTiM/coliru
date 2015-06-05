#include <tuple>
#include <utility>
#include <type_traits>

template<class S, class E>
struct edge {
    constexpr static bool exists = false;
};

struct Start {};
struct Point1 {};
struct Point2 {};
struct Point3 {};
struct End {};

struct None {};

#define CREATE_EDGE(S,E) template<> struct edge<S, E> { \
    constexpr static bool exists = true; \
}

CREATE_EDGE(Start, Point1);
CREATE_EDGE(Point1, Point2);
CREATE_EDGE(Point1, Point3);
CREATE_EDGE(Point2, End);
CREATE_EDGE(Point3, End);

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

template<class L, class... Ts>
using append = typename L::template append<Ts...>;

template<class L, size_t N>
using get = typename L::template get<N>;

// Build a list out of repeating a type N times
template<class Seq, class>
struct repeat_impl;
    
template<size_t... Is, class T>
struct repeat_impl<std::index_sequence<Is...>, T>{
    template<size_t> using _ = T;
    using type = type_list<_<Is>...>;
};
    
template<class T, size_t N>
using make_repeat_list = typename repeat_impl<std::make_index_sequence<N>, T>::type;

// Get the Nth element of L, where N is the index of T in All.
template<class L, class T, class All, size_t N = All::template index_of<T>()>
using retrieve = get<L, N>;

// Construct the path given Result, where Result[N] = the previous node on the path from S to All[N] if it exists, or None otherwise.
template<class S, class E, class All, class Result, bool has_path = !std::is_same<retrieve<Result, E, All>, None>::value>
struct do_result {
    // Current = current end of list
    template<class Current, bool = std::is_same<S, Current>::value>
    struct builder {
        constexpr static size_t I = All::template index_of<Current>();
        using prev = get<Result, I>;
        using step_t = edge<prev, Current>;
        using type = append<typename builder<prev>::type, step_t>;
    };
    template<class T>
    struct builder<T, true> { using type = type_list<>; };
    
    using type = typename builder<E>::type;
};

template<class S, class E, class All, class Result>
struct do_result<S, E, All, Result, false> {
    // has no path
    using type = None;
};


// BFS
template<class S, class E, class All, class ToBeProcessed, class Result> struct BFS_impl;

// nothing to process
template<class S, class E, class All, class Result>
struct BFS_impl<S, E, All, type_list<>, Result> : do_result<S, E, All, Result>{
};

// Do the next step of BFS; T is the next node to be processed, and Ts... are the other nodes that require processing.
template<class S, class E, class All, class Result, class T, class... Ts>
struct BFS_next {
    
    // If an edge from T to another node N exists and R[N] is None, then set R[N] = T.
    template<class R, class A>
    struct add_reachable;
    
    template<class... T1s, class... AllT>
    struct add_reachable<type_list<T1s...>, type_list<AllT...>>{
        using type = type_list<std::conditional_t<edge<T, AllT>::exists && std::is_same<T1s, None>::value, T, T1s>...>;
    };
    
    using new_result = typename add_reachable<Result, All>::type;
    
    // If a previously unreachable node has become reachable, add it to the list of nodes to be processed.
    template<class TBP, class OR, class NR, class A>
    struct compute_new_proc;
    
    template<class TBP, class OR1, class NR1, class A1, class... ORs, class... NRs, class... As>
    struct compute_new_proc<TBP, type_list<OR1, ORs...>, type_list<NR1, NRs...>, type_list<A1, As...>>
         : compute_new_proc<append<TBP, A1>, type_list<ORs...>, type_list<NRs...>, type_list<As...>> {};
         
    template<class TBP, class R, class A1, class... ORs, class... NRs, class... As>
    struct compute_new_proc<TBP, type_list<R, ORs...>, type_list<R, NRs...>, type_list<A1, As...>>
         : compute_new_proc<TBP, type_list<ORs...>, type_list<NRs...>, type_list<As...>> {};
         
    template<class TBP>
    struct compute_new_proc<TBP, type_list<>, type_list<>, type_list<>> { using type = TBP; };
    
    using new_proc = typename compute_new_proc<type_list<Ts...>, Result, new_result, All>::type;
        
    using type = typename BFS_impl<S, E, All, new_proc, new_result>::type;
};

// If E is reachable, stop.
// Otherwise, recurse.
template<class S, class E, class All, class Result, class T, class... Ts>
struct BFS_impl<S, E, All, type_list<T, Ts...>, Result> 
: std::conditional_t<
    std::is_same<retrieve<Result, E, All>, None>::value,
    BFS_next<S, E, All, Result, T, Ts...>,
    do_result<S, E, All, Result>> { };


template<class S, class E, class A>
using BFS = BFS_impl<S, E, A, type_list<S>, make_repeat_list<None, A::size>>;


using all_points = type_list<Start, Point1, Point2, Point3, End>;

template<class> class TD;
using T = BFS<Start, End, all_points>::type;

int main(){
    TD<T> t;
}
