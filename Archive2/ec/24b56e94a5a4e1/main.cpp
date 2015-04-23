
template <typename T>
struct foo {};

template <bool>
struct bar {};

template <typename I>  // oops
void test()
{
    foo<bar<(I < 4)>> f;
}

int main()
{
    
}