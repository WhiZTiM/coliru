#include <iostream>

class decimal_t{
public:
    int64_t val;
    uint8_t precision;
    constexpr decimal_t(int64_t val, uint8_t precision): val(val), precision(precision){}
};

constexpr decimal_t operator"" _dec(const char * t , std::size_t s){
    int64_t n=0;
    int8_t prec=0;
    bool negative=false;
    for(int i=0; i<s; ++i){
        if(t[i]>='0' && t[i]<='9')n=n*10+(t[i]-'0');
        if(prec) ++prec;
        if(t[i]=='.') prec=1;
        negative=negative || t[i]=='-';
    }
    if(prec) --prec;
    if(negative) n*=-1;
    return decimal_t(n,prec);
}

int main() {
    std::cout << "12-3"_dec.val << '\n';
}
