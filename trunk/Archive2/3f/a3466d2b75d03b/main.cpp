#include <iostream>

template<typename T, int I> class VecN {
    public:    
    T vec[I];
     
    //variadic constructor
    //template <typename... T2>
    //VecN(T2... rest) : vec{ rest... }{
    //}
    
            VecN(const T& x){//constructor
            for (size_t i = 0; i<I; ++i)
                vec[i] = T(x);
        }
    
    //used by variadic constructor
    void setRecurse(){
    }
    
    //used by variadic constructor
    template <typename... T2>
    void setRecurse(T x, T2...rest){
        vec[I - sizeof...(rest) - 1] = x;
        setRecurse(rest...);
    }
    
    //variadic constructor
    template <typename... T2>
    VecN(T x1, T x2, T2... rest){
        static_assert(sizeof...(T2) + 2 == I, "wrong number of parameters for variadic constructor");
        vec[0]=x1;
        vec[1]=x2;
        setRecurse(rest...);
    }
    
    void print() const {
        if(I>0)printf("%e", vec[0]);
        for (size_t i = 1; i < I; i++)
            printf("\n%e", vec[i]);
    }
};

int main()
{
    VecN<double, 4> x(1.0);
    x.print();
}
