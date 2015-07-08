#include <iostream>
#include <string>
#include <vector>
#include <utility>

template<char...> struct string {};

constexpr struct {
  template<typename T>
  constexpr operator T() const {
    return T{};
  }
} to_value{};

template<typename S, std::size_t...Ints>
constexpr decltype(auto) make_string_helper(S, std::index_sequence<Ints...>) {
  return string<S::data()[Ints]...>{};
}

template<typename S>
constexpr decltype(auto) make_string(S) {
  constexpr decltype(auto) x = make_string_helper(S{}, std::make_index_sequence<S::size()>());
  return x;
}

#define FMT_STRING(x) make_string(false ? []{                         \
  constexpr struct {                                                  \
    static constexpr decltype(auto) data() { return x; }              \
    static constexpr decltype(auto) size() { return sizeof(data()); } \
  } deduce{};                                                         \
  return deduce;                                                      \
}() : to_value)

template<typename Arg0, typename...Args, char...Chars>
constexpr bool check(string<Chars...> fmt) {
    const char str[] = { Chars..., 0 };
    size_t pos = 0;
    while(pos < sizeof...(Chars)) {
        switch(str[pos]) {
        case '%':
            switch(str[pos+1]) {
            case 's':
                if( !std::is_same<Arg0, const char *>::value ) // check if types match 
                    return false;
                pos += 2;
                break;
            }
            break;
        default:
            pos += 1;
            break;
        }
    }
    return true;
}

template<typename...Args, char...Chars>
void printxf(string<Chars...> fmt, Args...args) {
    static_assert(check<Args...>(fmt), "whatever");
}

int main() {
    printxf(FMT_STRING("sdgfasg%sadhfsghj"), "asd");
    // printxf(FMT_STRING("adfhdhj%s"), 0); // compile-time error
}
