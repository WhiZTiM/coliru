

int n = 1;
short s = 2;


template<typename T, T*>
struct meta_data;


template<>
struct meta_data<decltype(n), &n>
{ 
};

template<>
struct meta_data<decltype(s), &s>
{
    void something()
    {
    }
};


int main()
{
    meta_data<decltype(s), &s> obj;
    obj.something();
}