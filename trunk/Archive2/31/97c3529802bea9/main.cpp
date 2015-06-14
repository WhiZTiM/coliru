#include <iostream>
#include <memory>
#include <utility>
#include <array>
#include <cxxabi.h> // for abi::__cxa_demangle
 
struct A {
    A(int&& n) : _a{n} { std::cout << "rvalue overload, n=" << n << "\n"; }
    A(int& n) : _a{n} { std::cout << "lvalue overload, n=" << n << "\n"; }
   friend std::ostream & operator<< ( std::ostream & o, const A& obj ) { return o << obj._a; }
   private:
   int _a;
};
 
class B {
public:
    template<class T1, class T2, class T3>
    B(T1&& t1, T2&& t2, T3&& t3) :
        a1_{std::forward<T1>(t1)},
        a2_{std::forward<T2>(t2)},
        a3_{std::forward<T3>(t3)}
    {
    }
   friend std::ostream & operator<< ( std::ostream & o, const B& obj ) { return o << "B{" << obj.a1_ << "," << obj.a2_ << "," << obj.a3_ << "}"; } 
private:
    A a1_, a2_, a3_;
};
 
template<class T, class U>
std::unique_ptr<T> make_unique1(U&& u)
{
    return std::unique_ptr<T>(new T(std::forward<U>(u)));
}
 
template<class T, class... U>
std::unique_ptr<T> make_unique(U&&... u)
{
    return std::unique_ptr<T>(new T(std::forward<U>(u)...));
}

template<typename...> struct Tuple {};
template<typename T1, typename T2> struct Pair {};
 
template<class ...Args1> struct zip {
    template<class ...Args2> struct with {
        typedef Tuple<Pair<Args1, Args2>...> type;
//        Pair<Args1, Args2>... is the pack expansion
//        Pair<Args1, Args2> is the pattern
    };
};
 
typedef zip<short, int>::with<unsigned short, unsigned>::type T1;
// Pair<Args1, Args2>... expands to
// Pair<short, unsigned short>, Pair<int, unsigned int> 
// T1 is Tuple<Pair<short, unsigned short>, Pair<int, unsigned>>
 
//typedef zip<short>::with<unsigned short, unsigned>::type T2;
// error: pack expansion contains parameter packs of different lengths

template<typename T> using Type = T;
template<typename... Ts, int... N> void g( Type<Ts[N]>&... ) {}

template<typename T> using TypeConvert = T;
//template<> struct TypeConvert<int> { using type = signed int; };

template<class... Types> struct OutStruct {};
template<class... Types> struct OutType {
    typedef std::tuple< TypeConvert<Types>... > Tuple;
    Tuple _tuple;
    OutType( Types&& ... args ) {}
};



//=======================================
// http://en.cppreference.com/w/cpp/utility/functional/reference_wrapper
// Possible implementation
template <class T>
class std_reference_wrapper {
public:
  // types
  typedef T type;
 
  // construct/copy/destroy
  std_reference_wrapper(T& ref) noexcept : _ptr(std::addressof(ref)) {}
  std_reference_wrapper(T&&) = delete;
  std_reference_wrapper(const std_reference_wrapper&) noexcept = default;
 
  // assignment
  std_reference_wrapper& operator=(const std_reference_wrapper& x) noexcept = default;
 
  // access
  operator T& () const noexcept { return *_ptr; }
  T& get() const noexcept { return *_ptr; }
 
private:
  T* _ptr;
};



//=======================================
//http://en.cppreference.com/w/cpp/utility/tuple/make_tuple
// Possible implementation

template <class T>
struct special_decay
{
    using type = typename std::decay<T>::type;
};
 
template <class T>
struct special_decay<std_reference_wrapper<T>>
{
    using type = T&;
};
 
template <class T>
using special_decay_t = typename special_decay<T>::type;
 
template <class... Types>
auto std_make_tuple(Types&&... args)
{
    std::cout << "[" << __PRETTY_FUNCTION__ << "]";
    return std::tuple<special_decay_t<Types>...>(std::forward<Types>(args)...);
}

//=======================================
    template<typename T> struct TraceType final {
        static std::string demangle_type_name() {
            int status;
            std::string tname = typeid(T).name();
            char *demangled_name = abi::__cxa_demangle(tname.c_str(), NULL, NULL, &status);
            if(status == 0) {
                tname = demangled_name;
                std::free(demangled_name);
            }
            return tname;
        }

        static std::string name() {
            static std::string tname = demangle_type_name();
            return tname;
        }
        
    };


    // helper function to print a tuple of any size
    template<class Tuple, size_t N>
      struct TuplePrinter {
    static void print(const Tuple& t) 
	{
	  TuplePrinter<Tuple, N-1>::print(t);
	  std::cout << ", " << std::get<N-1>(t) << "{" << TraceType<decltype(std::get<N-1>(t))>::name() << "}";
	}
      };
    
    template<class Tuple>
      struct TuplePrinter<Tuple, 1> {
      static void print(const Tuple& t) 
      {
	std::cout << std::get<0>(t) << "{" << TraceType<decltype(std::get<0>(t))>::name() << "}";
      }
    };
    
    template<class... Args>
      void print(const std::tuple<Args...>& t) 
      {
    std::cout << __PRETTY_FUNCTION__ << "(";
	TuplePrinter<decltype(t), sizeof...(Args)>::print(t);
	std::cout << ")\n";
      }
      
    template<class T>  static void print1( const T&& obj ) { std::cout << "{" << __PRETTY_FUNCTION__ << "}" << obj; }

    template<class T>  static void print1( const std::unique_ptr<T>& obj ) { std::cout << "{" << __PRETTY_FUNCTION__ << "}" << *obj; }
      
    template<class T, class... Args>
      void print(const T&& t, Args&&... args) 
      {
        std::cout << "{" << __PRETTY_FUNCTION__ << "}(";
        print1(std::forward<T>(t));
        print(args...);
        std::cout << ")\n";
      }
      
    template<class T, class... Args>
      void print(const T&& t, Args&&... args) 
      {
        std::cout << __PRETTY_FUNCTION__ << "(";
        TuplePrinter<decltype(t), sizeof...(Args)>::print(t);
	    std::cout << ")\n";
      }
    // end helper function


int main()
{   
    auto p1 = make_unique1<A>(2); // rvalue
    int i = 1;
    auto p2 = make_unique1<A>(i); // lvalue
 
    std::cout << "B\n";
    auto t = make_unique<B>(2, i, 3);
    
    auto t2 = std_make_tuple( 2, i, 3, '?', "tuple" );
    print( t2 );
    print( t );
    print( 'help', 1.2f );
//    OutType Foo( 1 );// transform var
}