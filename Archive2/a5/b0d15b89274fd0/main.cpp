template <typename T1, typename T2 = void>
struct Tuple
{
    T1 Item1;
    T2 Item2;
};

template <typename T1>
struct Tuple<T1, void>
{
    T1 Item1;
};

int main()
{
    Tuple<int> t1;
    Tuple<int, float> t2;
    
    (void)t1;(void)t2;
}
