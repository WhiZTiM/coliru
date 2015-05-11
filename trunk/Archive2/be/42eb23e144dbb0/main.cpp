template<typename A>
struct box {
    template<typename B>
    struct diamond_back {
        template<typename C>
        struct painted {
            template<typename X>
            static void down();
        };
    };
};

template<typename A>
template<typename B>
template<typename C>
template<typename X>
void box<A>::diamond_back<B>::painted<C>::down() {}

int main()
{
    box<short>::diamond_back<int>::painted<long>::down<long long>();
}
