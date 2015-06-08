#include <iostream>
#include <string>
#include <vector>

template<typename T, int I> class VecN {
        //template<typename T, size_t J> friend class VecN;//Let's be friends with ourselves!
    public:    
    T vec[I];
    
    VecN(){//constructor
        for (int i = 0; i<I; ++i)
            vec[i] = T(0);
    }
    VecN(const T& x){//constructor
        for (int i = 0; i<I; ++i)
            vec[i] = T(x);
    }
    template<typename F> auto map(F f) -> VecN<decltype(f(*vec)), I> {
        VecN<decltype(f(*vec)), I> dst;
        for (int i = 0; i < I; ++i)
            dst[i] = f(vec[i]);
        return dst;
    }
    T& operator[](size_t i) {//Used if VecN is an rvalue
        return vec[i];
    }
};

int main()
{
    VecN<VecN<double, 3>, 3> x(0);
    x.map([](const VecN<double, 3> x){return VecN<double, 3>(1);});
}
