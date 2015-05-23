void foo()
{
    struct bar
    {
        template<typename T>
        void operator()(T x)
        {
        }
    };
}