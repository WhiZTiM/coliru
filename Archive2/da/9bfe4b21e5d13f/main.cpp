template <class = void>
struct A {
    int i;
    
    static auto& truc() {
        static char arr[sizeof(A)];
        return arr;
    }
};

int main()
{
    auto array = A<>::truc();
}