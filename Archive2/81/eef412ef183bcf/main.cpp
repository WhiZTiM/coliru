template <typename T>
struct A
{
    T item;
};

template <typename T>
struct B
{
	T item;
};

template <typename T>
struct C final : A<T>,B<T>
{

};

int main(int argc, char* argv[])
{
	C<int> See;
	auto foo = See.A::item;
}