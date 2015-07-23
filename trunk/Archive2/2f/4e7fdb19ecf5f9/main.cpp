#include <iostream>
#include <utility>
#include <tuple>
#include <chrono>

template<typename A, typename B>
struct pair {
    A first;
    B second;
    constexpr pair(A first, B second) : first(first), second(second) {}
};


struct strwrp {
    static constexpr size_t nil = -1;
    
    const char *cstr;
    size_t size;
 
    template<size_t N>
	constexpr strwrp(const char (&arr)[N]) : cstr(arr), size(N-1) {}
    constexpr strwrp(const char *cstr, size_t size) : cstr(cstr), size(size) {}
	constexpr char operator[](size_t i) const { return cstr[i]; };
    constexpr strwrp substr(size_t offset, size_t n) const { return strwrp(cstr+offset, n); }
    constexpr strwrp before(size_t i) const { return substr(0, i); }
    constexpr strwrp after(size_t i) const { return substr(i, size-i); }
    constexpr bool isEmpty() const { return size == 0; }
    
    constexpr pair<size_t, strwrp> parsePlaceholder() const {
        constexpr auto err = pair<size_t, strwrp>(nil, "");
        
        if (size < 3 || cstr[0] != '{') return err;
        
        size_t acc = 0;
        size_t i = 0;
        for (i = 1; i < size-1; i++) {
            char c = cstr[i];
            if (c == '}') break;
            if (!('0' <= c && c <= '9')) return err;
            acc = 10 * acc + c - '0';
        }
        if (cstr[i] != '}') return err;
        
        return pair<size_t, strwrp>(acc, after(i+1));
    }
    
    constexpr pair<strwrp, strwrp> parseFormat() const {
        for (size_t i = 0; i < size; i++) {
            if (cstr[i] == '{') {
                return pair<strwrp,strwrp>(before(i), after(i));
            }
        }
        return pair<strwrp,strwrp>(*this, "");
    }
    
};

template<typename Fmt, size_t... index>
void printChars(std::ostream &out, std::index_sequence<index...>) {
    constexpr char cs[] = { Fmt::getString()[index]..., '\0' };
    out << cs; 
}

template<typename Fmt, typename... Args>
void printString(std::ostream &out, Args&&... args);

template<typename Fmt, typename... Args>
void printPlaceholder(std::ostream &out, std::false_type, Args&&... args) {
    constexpr auto parsed = Fmt::getString().parsePlaceholder();
    constexpr size_t n = parsed.first;
    static_assert(n != strwrp::nil, "invalid placeholder");
    static_assert(n < sizeof...(Args), "need moar args!");
    struct FormatString {
        static constexpr strwrp getString() { return parsed.second; }
    };
    
    std::cout << std::get<n>(std::make_tuple(args...));
    printString<FormatString>(out, std::forward<Args>(args)...);
}

template<typename Fmt, typename... Args>
void printPlaceholder(std::ostream&, std::true_type, Args&&...) {}

template<typename Fmt, typename... Args>
void printString(std::ostream &out, Args&&... args) {
    constexpr auto parsed = Fmt::getString().parseFormat();    
    using IsEmpty = std::integral_constant<bool, parsed.second.isEmpty()>;
    struct FormatString {
        static constexpr strwrp getString() { return parsed.second; }
    };
    
    printChars<Fmt>(out, std::make_index_sequence<parsed.first.size>());
    printPlaceholder<FormatString>(out, IsEmpty(), std::forward<Args>(args)...);
}

struct ConstexprWay {
    static void f() {
        struct FormatString {
            static constexpr strwrp getString() {
                return strwrp("This {0} is {1} a {2} test!!! {3}{4}{5}{6}{7}{8}{9}{10}{11}{12}{13}{14}{15}{16}{17}{18}{19}{20}!!!!\n");
            }
        };
        
        printString<FormatString>(std::cout, 123412, "sadofijaoifjasd", 1234123.234123, "asdf", "asdf", "asdf", "asdf", "asdf", "asdf", "asdf", "asdf", "asdf", "asdf", "asdf", "asdf", "asdf", "asdf", "asdf", "asdf", "asdf", "asdf");
    }
};

struct OldWay {
    static void f() {
        std::cout << "This " << 123412 << " is " << "sadofijaoifjasd" << " a " << 1234123.234123 << " test!!! " << "asdf" << "asdf" << "asdf" << "asdf" << "asdf" << "asdf" << "asdf" << "asdf" << "asdf" << "asdf" << "asdf" << "asdf" << "asdf" << "asdf" << "asdf" << "asdf" << "asdf" << "asdf" << "!!!!\n";
    }
};

template<typename F>
int test() {
    auto before = std::chrono::system_clock::now();
    for (int i = 0; i < 250; i++) {
        F::f();
    }
    auto after = std::chrono::system_clock::now();
    
    return std::chrono::duration_cast<std::chrono::microseconds>(after - before).count();
}

int main() {
    std::cout.sync_with_stdio(false);
    
    int y = test<OldWay>();
    int x = test<ConstexprWay>();
    
    std::cout << "ConstexprWay: " << x << " OldWay: " << y << std::endl;
    
    
    return 0;
}