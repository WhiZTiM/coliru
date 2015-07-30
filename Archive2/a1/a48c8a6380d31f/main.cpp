// Aaron McDaid aaron.mcdaid@gmail.com

// This answer:  http://stackoverflow.com/a/31735637/146041

// To this question:  http://stackoverflow.com/questions/31728625/efficient-direct-initialization-of-a-stdvector
#include<iostream>
#include<vector>
#include<array>
#include<tuple>
#include<memory>

struct A {
  A(int n, std:: string s) : n(n) {
    std::cout << n << " created (" << s << ")" << std::endl;
  }
  A(int n) : n(n) {
    std::cout << n << " created" << std::endl;
  }
  ~A() {
    std::cout << n << " erased" << std::endl;
  }
  A(const A &a) : n(a.n) {
    std::cout << n << " copied" << std::endl;
  }
  A(A &&a) : n(std:: move(a.n)) {
    std::cout << n << " moved" << std::endl;
  }
  A &operator=(const A &a) {
    n = a.n;
    std::cout << n << " assigned" << std::endl;
    return *this;
  }
  A &operator=(A &&a) {
    n = std::move(a.n);
    std::cout << n << " move-assigned" << std::endl;
    return *this;
  }
  bool operator<(const A &a) const {
    return n < a.n;
  }
  int n;
};

template<typename Target>
struct ConvInterface {
    virtual Target convert_to_target_type() const = 0;
    virtual ~ConvInterface() {}
};

// These next few templates are just to copy something
// useful from C++14. http://en.cppreference.com/w/cpp/utility/integer_sequence
template<size_t ... is>
struct my_index_sequence { // based on C++14s std:: index_sequence
    template<size_t extra>
    struct append {
        typedef my_index_sequence<is..., extra> type;
    };
};
template<size_t N>
struct make_my_index_sequence {
    typedef typename make_my_index_sequence<N-1>:: type :: template append<N-1>:: type type;
};
template<>
struct make_my_index_sequence<1> {
    typedef my_index_sequence<0> type;
};
template<typename T, typename... Args>
std::unique_ptr<T> make_unique(Args&&... args)
{
        return std::unique_ptr<T>(new T(std::forward<Args>(args)...));
}


template<typename Target, typename ...T>
struct Conv : public ConvInterface<Target> {
    std::tuple<T...> the_pack_of_constructor_args;
    Conv(std::tuple<T...> &&t) : the_pack_of_constructor_args(std:: move(t)) {}

    Target convert_to_target_type () const override {
        using idx = typename make_my_index_sequence<sizeof...(T)> :: type;
        return foo(idx{});
    }
    template<size_t ...i>
    Target foo(my_index_sequence<i...>) const {
        // This next line is the main line, constructs
        // something of the Target type (see the return
        // type here) by expanding the tuple.
        return {
                std:: forward
                    < typename std:: tuple_element < i , std::tuple<T...> > :: type >
                    (std:: get<i>(the_pack_of_constructor_args))
            ...
        };
    }
};

template<typename Target, typename ...T>
auto make_Conv_from_tuple(std::tuple<T...>&& tuple) -> std:: unique_ptr<Conv<Target, T...> > {
    return ::make_unique< Conv<Target, T...> >(std:: move(tuple));
}

template<typename Target>
struct UniquePointerThatConverts {
    std:: unique_ptr<ConvInterface<Target>> p; // A pointer to an object
               // that implements the desired interface, i.e.
               // something that can convert to the desired
               // type (Target).

    template<typename Tuple>
    UniquePointerThatConverts(Tuple&& p_)
    : p ( make_Conv_from_tuple<Target>(std:: move(p_)) )
    {
        //cout << __PRETTY_FUNCTION__ << endl;
    }
    operator Target () const {
        return p->convert_to_target_type();
    }
};

template<typename Target, typename ...PackOfTuples>
auto make_vector_efficiently(PackOfTuples&&... args)
    -> std::vector<Target>
{
    auto inits = { UniquePointerThatConverts<Target>(std::forward<PackOfTuples>(args))...};
    return std::vector<Target> {std::begin(inits), std::end(inits)};
}

template<typename ...T>
std:: tuple<T&&...> pack_for_later(T&&... args) {
        // this function is really just a more
        // 'honest' make_tuple - i.e. without any decay
    return std:: tuple<T&&...> (std::forward<T>(args)...);
}

int main() {
    auto v2 = make_vector_efficiently<A>(
            pack_for_later(1)
            ,pack_for_later(2,"test the two-argument constructor")
            ,pack_for_later(3)
            );
    auto v3 = make_vector_efficiently<std:: unique_ptr<int>> (
            pack_for_later( make_unique<int>(3) )
            ,pack_for_later( make_unique<int>(3) )
            );
}
