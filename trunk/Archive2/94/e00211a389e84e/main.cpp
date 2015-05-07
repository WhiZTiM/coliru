#include <tuple>


template<typename ...T>
int test(T...);


int impl_test(int a, int b, int c, int d)
{
    return a + b + c + d;
}


int impl_test(std::array<int, 4> arr)
{
    return arr[0] + arr[1] + arr[2] + arr[3];
}



struct abcd
{
    int a = 1;
    int b = 2;
    int c = 3;
    int d = 4;
};


int impl_test(abcd s)
{
    return s.a + s.b + s.c + s.d;
}


int impl_test(std::tuple<int, int, int, int> tup)
{
    return
        + std::get<0>(tup)
        + std::get<1>(tup)
        + std::get<2>(tup)
        + std::get<3>(tup);
}

    
int main()
{
    test(1, 2, 3, 4);
    test(std::array<int, 4>{1, 2, 3, 4});
    test(abcd());
    test(std::make_tuple(1, 2, 3, 4)); 
}