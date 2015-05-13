#include <iostream>

template< typename ... Args >
static constexpr size_t
args_size( Args&&... args ) { return sizeof ... (args); }

#define FOO(...) do { static thread_local BAR<__LINE__,__COUNTER__,args_size(__VA_ARGS__)> bar(__FILE__,__func__,#__VA_ARGS__,##__VA_ARGS__); } while (false)

template<size_t LEN> using StrLit = const char (&)[LEN]; 

template<class ... Types> struct Tuple {};

template< size_t LINE, size_t COUNTER, size_t SIZE >
struct BAR {
    
    template<size_t FILE_N, size_t FUNC_N, size_t ARGS_N, typename ... Args>
    /*constexpr*/ BAR( StrLit<FILE_N> str_file, StrLit<FUNC_N> str_func,StrLit<ARGS_N> str_args, Args&&...args ) {
        constexpr size_t NUM_ARGS = sizeof ... (args);
        std::cout << "sizeof(n) = " << sizeof(n) << " SIZE=" << SIZE << " NUM_ARGS=\"" << NUM_ARGS << " file: \"" << str_file << "\" func: \"" << str_func << "\" args: \"" << str_args << "\"\n";
    }
//    Tuple tuple = 
    int n[1+SIZE];
};
#define GCC_VERSION (__GNUC__ * 10000 \
                       + __GNUC_MINOR__ * 100 \
                       + __GNUC_PATCHLEVEL__)
int main() {
    std::cout << GCC_VERSION << '\n';
    FOO();
    for(int i=0; i<8; ++i) {
        FOO("i=",i,"now is the time for all good men to come to the aid of their country.");
    }
}
