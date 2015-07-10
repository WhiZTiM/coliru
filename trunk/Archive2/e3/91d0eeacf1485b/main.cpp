#include <iostream>
#include <locale>
#include <utility>

void sum_and_print_words() {
    int i = 0;
    bool read = false;
    char c;
    while(std::cin.get(c)) {
        if(!std::isspace(c, std::cin.getloc())) {
            i += c - '0';
            read = true;
        }else
        {
            std::cout << i << "\n";
            i = 0;
            read = false;
        }
    }
    if(read) {
        std::cout << i << "\n";
    }
}

template<typename InIt, typename Init>
struct reduce_while_result {
    Init result;
    InIt pos;
    bool succeeded;
};

template<typename InIt, typename Pred, typename BinOp, typename UnFun, typename T>
auto reduce_while(InIt b, InIt e, Pred p, BinOp o, UnFun u, T t) -> reduce_while_result<InIt, T> {
    bool succeeded = false;
    while(b != e) {
        auto c = *b;
        ++b;
        if(p(c)) {
            t = o(t, u(c));
            succeeded = true;
        }else
            return {t, b, succeeded};
    }
    return {t, b, succeeded};
}

int main()
{
    auto is_not_space = [](char c){ return !std::isspace(c); };
    auto char_to_int = [](char c){ return c - '0'; };
    
    std::istreambuf_iterator<char> b(std::cin);
    std::istreambuf_iterator<char> e{};
    while(b != e) {
        auto const r = reduce_while(b,e, is_not_space, std::plus<>{}, char_to_int, int{});
        if(r.succeeded)
            std::cout << r.result << "\n";
        b = r.pos;
    }
}