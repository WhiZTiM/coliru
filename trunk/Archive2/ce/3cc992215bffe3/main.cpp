template <typename...>
struct Tuple;

template <typename T1>
struct Tuple<T1>
{
    T1 Item;
};

template <typename T1, typename T2>
struct Tuple<T1, T2>
{
    T1 Item1;
    T2 Item2;
};

int main()
{
    Tuple<int> t1;
    Tuple<int, float> t2;
    
    (void)t1;(void)t2;
}
