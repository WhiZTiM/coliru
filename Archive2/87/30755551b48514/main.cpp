namespace A
{
    template <class T> struct some_class
    { /* some definition */ };
}

namespace B
{
    template <class T> using some_class = A::some_class<T>;
}

namespace B
{
    template <class T>
    decltype(auto) some_func(const some_class<T>& obj)
    { /* function definition */ }
}

int main() {
    
}