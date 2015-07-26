template <typename T>
struct base {
    T item;
};

template <typename T>
struct A : virtual base<T> {};

template <typename T>
struct B : virtual base<T> {};

template <typename T>
struct C final : A<T>, B<T>
{

};

int main(int argc, char* argv[])
{
	C<int> See;
	auto foo = See.item;
}