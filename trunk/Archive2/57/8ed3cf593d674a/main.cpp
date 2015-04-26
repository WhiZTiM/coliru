template <int>
void flag ();

template<int i>
struct writer {
    friend void flag<i>() noexcept;
};

template <bool B, int i=0>
struct dependent_writer : writer<i> {};

template<
  bool B = noexcept (flag<0>()),
  int    =   sizeof (dependent_writer<B>)
>
constexpr int f () {
	return B;
}

int main () {
	constexpr int a = f ();
	constexpr int b = f ();

	static_assert (a != b, "fail");
}
