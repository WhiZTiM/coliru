#include <iostream>

template<typename T>
struct reference_t {
    reference_t(const T& t) : ref(t) {}
	const T& ref;
};

template<typename Ref>
void print_ref(Ref R) {
	std::cout << R.ref << "\n";
}

int main() {
	int x = 3;
	reference_t<int> r1(2);
	reference_t<int> r2(x);

#ifdef WAT
	print_ref(r1);
#else
    std::cout << r1.ref << "\n";
#endif
	print_ref(r2);
    
	std::cout << r1.ref << "\n";
	std::cout << r2.ref << "\n";
}
