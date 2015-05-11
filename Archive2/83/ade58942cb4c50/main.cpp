#include <iostream>
#include <cstdint>
#include <cmath>

class decimal_t{
public:
    int64_t val;
    uint8_t precision;
    constexpr decimal_t(int64_t val, uint8_t precision): val(val), precision(precision){}

    decimal_t operator-() const{
        decimal_t d=*this;
        d.val*=-1;
        return d;
    }
/*
    decimal_t operator+(const decimal_t & other) const;
    decimal_t & operator+=(const decimal_t & other);

    decimal_t operator-(const decimal_t & other) const;
    decimal_t & operator-=(const decimal_t & other);

    decimal_t operator*(const decimal_t & other) const;
    decimal_t & operator*=(const decimal_t & other);

    decimal_t operator/(const decimal_t & other) const;
    decimal_t & operator/=(const decimal_t & other);

    decimal_t operator%(const decimal_t & other) const;
    decimal_t & operator%=(const decimal_t & other);

    decimal_t & operator=(const decimal_t & other);
*/
};

std::ostream & operator<<(std::ostream& o, const decimal_t & d){
    int64_t p=pow(10,d.precision);
    o<<(d.val/p)<<".";
    o.width(d.precision);
    o.fill('0');
    o<<(abs(d.val)%p);
    return o;
}

constexpr decimal_t operator"" _dec(const char * s){
    int64_t n=0;
    int8_t prec=0;
    for(; *s; ++s){
        if((*s)>='0' && (*s)<='9')n=n*10+((*s)-'0');
        if(prec) ++prec;
        if((*s)=='.') prec=1;
    }
    if(prec) --prec;
    return decimal_t(n,prec);
}


int main(int argc, char * argv[]){

    std::cout<< 123.22_dec <<std::endl;
    std::cout<< -123.022_dec <<std::endl;
    std::cout<< sizeof(decimal_t) <<std::endl;


}