struct A
{
    template <typename T>
	struct B {};
};

template <typename T>
void foo()
{
	T::B<int> a; // Błąd!
}

int main()
{
    
}
