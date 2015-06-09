#include <iostream>
#include <type_traits>

void populateNext(char*, std::size_t) {}

struct A {
    A(A const&) {std::cout << __PRETTY_FUNCTION__<< '\n';}
	A(A&&) {std::cout << __PRETTY_FUNCTION__<< '\n';}
	A() {std::cout << __PRETTY_FUNCTION__<< '\n';}
	~A() {std::cout << __PRETTY_FUNCTION__<< '\n';}
};

template <typename Record>
std::enable_if_t</*std::is_trivially_copyable<Record>{},*/ true, Record> getNext() {
	std::aligned_storage_t<sizeof(Record)> arr;
	populateNext(reinterpret_cast<char*>(&arr), sizeof arr);
	return reinterpret_cast<Record&&>(arr);
}

int main() {
    auto r = getNext<A>();
}
