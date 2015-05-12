#include <utility>
#include <iostream>

    template<class T>struct tag{using type=T;};
    template<class Tag>using type=typename Tag::type;

    template<class...>struct types{using type=types;};

    template<class...Ts>
    struct cat;
    template<class...Ts>
    using cat_t=type<cat<Ts...>>;

    template<class...As, class...Bs, class...Ts>
    struct cat< types<As...>, types<Bs...>, Ts... >:
      cat< types<As...,Bs...>, Ts... >
    {};
    template<class...Ts>
    struct cat< types<Ts...> >:
      types<Ts...>
    {};
    template<>
    struct cat<>:
      types<>
    {};
/* Not needed
    template<class X, size_t N>
    struct split;
    template<class X>
    using left_t = typename X::left;
    template<class X>
    using right_t = typename X::right;
    template<class L, class R>
    struct halves {
      using left=L;
      using right=R;
    };

    template<class...Ts>
    struct split< types<Ts...>, 0>:
      halves<types<>, types<Ts...>>
    {};
    template<class T0, class...Ts>
    struct split<types<T0, Ts...>, 1>:
      halves<types<T0>, types<Ts...>>
    {};

    template<class...Ts, size_t N>
    struct split<types<Ts...>,N> {
    private:
      using quarter_1 = split<types<Ts...>, N/2>;
      using quarter_2 = split< right_t<quarter_1>, N-N/2 >;
    public:
      using left = cat_t< left_t<quarter_1>, left_t<quarter_2> >;
      using right = right_t< quarter_2 >;
    };
    */
// Now, so we can operate on sequences:

    template<class Seq>
    struct seq_to_types;
    template<class Seq>
    using seq_to_types_t=type<seq_to_types<Seq>>;
    template<class T, T...ts>
    struct seq_to_types< std::integer_sequence<T,ts...> >:
      tag< types< std::integral_constant<T,ts>... > >
    {};
    template<class T, class Rhs>
    struct types_to_seq:tag<Rhs>{};
    template<class T, class types>
    using types_to_seq_t=type<types_to_seq<T,types>>;
    template<class T, T...ts>
    struct types_to_seq<T, types<std::integral_constant<T, ts>...>>:
      tag<std::integer_sequence<T, ts...>>
    {};
    template<class T, class...Ts>
    struct types_to_seq<T, types<Ts...>>:
      types< types_to_seq_t<T, Ts>... >
    {};
// now we can take a `std::integer_sequence<int, 1,2,3>` and produce `types< std::integral_constant<int,1>, std::integral_constant<int,2>, std::integral_constant<int,3> >` which in my opinion is far easier to work with.  We can even map back.

    template<template<class...>class M, class Seq>
    struct mapper;
    template<template<class...>class M, class Seq>
    using mapper_t=type<mapper<M,Seq>>;
    template<template<class...>class M, class...Ts>
    struct mapper<M, types<Ts...>>:
      types<M<Ts>...>
    {};
// `mapper_t< some_metafunction, types<blah...>>` will map each `blah` through the `some_metafunction` to produce a new list of types.

    template<template<class...>class F, class X>
    struct bind_1st {
      template<class...Ts>
      using apply=F<X,Ts...>;
    };
// which can use do a cross product easily (together with `cat_t` and `mapper_t`).

    template<class...Ts>
    struct cross_product:types<types<>>{};
    template<class...Ts>
    using cross_product_t=type<cross_product<Ts...>>;

    template<class...T0s, class...Ts>
    struct cross_product<types<T0s...>, Ts...>:cat<
      mapper_t<
        bind_1st<cat_t, types<T0s>>::template apply,
        cross_product_t<Ts...>
      >...
    >{};
// which I think is slick.

    template<class...Seq>
    struct coords;
    template<class...Seq>
    using coords_t=type<coords<Seq...>>;
    template<class T, T...ts, class...Ts>
    struct coords< std::integer_sequence<T,ts...>, Ts... >:
      types_to_seq<
        T,
        cross_product_t<
          seq_to_types_t<std::integer_sequence<T,ts...>>,
          seq_to_types_t<Ts>...
        >
      >
    {};
// should explode nicely.

template<size_t N>
void indent() {
    for (size_t i = 0; i < N;++i)
        std::cout << ' ';
}

template<size_t N=0, class T>
void print( std::integer_sequence<T> ) {}

template<size_t N=0, class T, T t0, T...ts>
void print( std::integer_sequence<T, t0, ts...> ) {
    using unused=int[];
    indent<N>();
    std::cout << t0;
    (void)unused{(0,(
        std::cout << ',' << ts
    ),void(),0)...};
}


template<size_t N=0, class...Ts>
void print(types<Ts...>) {
    using unused=int[];
    std::cout << "{\n";
    (void)unused{(0,(
        indent<N+1>(), print<N+1>(Ts{}), std::cout << '\n'
    ),void(),0)...};
    indent<N>();
    std::cout << '}';
}

int main() {
    using one_two_three = std::integer_sequence<int, 1,2,3>;
    types< types<int,int>, types<int,double> > x = cross_product_t< types<int>, types<int, double> >{};
    print( coords_t< one_two_three, one_two_three, one_two_three >{} );
}