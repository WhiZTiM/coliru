template <typename T> struct print_with_incomplete_type;

int main()
{
    auto i{ 1, 2, 3 };
    print_with_incomplete_type<decltype(i)>{};
} 
