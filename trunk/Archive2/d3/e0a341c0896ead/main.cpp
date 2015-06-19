struct A
{
    template <typename T>
	struct B {};
};

template <typename T>
void foo()
{
    typename T::template B<int> a; // OK!
}

int main()
{
    
}
