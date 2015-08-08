#include <iostream>
#include <memory>

enum Enum {A,B,C,D, NumEnums};

struct Base {
    virtual void print() const = 0;
};

template <Enum...enums> struct Thing : public Base
{
	void print() const override
	{
		int dummy[] = {0, ((std::cout << enums << " "), 0)...};
        (void) dummy; // avoid warning for unused var
        std::cout << std::endl;
	}
	
};


template <std::size_t N>
std::unique_ptr<Base> make_thing3()
{
	constexpr Enum a2 = Enum(N % NumEnums);
	constexpr Enum a1 = Enum((N / NumEnums) % NumEnums);
	constexpr Enum a0 = Enum((N / NumEnums / NumEnums) % NumEnums);
    return std::make_unique<Thing<a0, a1, a2>>();
}

template <std::size_t... Is>
std::unique_ptr<Base> make_thing3(std::size_t index, std::index_sequence<Is...>)
{
	using maker = std::unique_ptr<Base>();
	maker* fs[] = {&make_thing3<Is>...};
	
	return fs[index]();
}

std::unique_ptr<Base> make_thing3(const std::array<Enum, 3u>& a)
{
	std::size_t index = 0;
	for (Enum e : a) {
		index *= NumEnums;
		index += e;
	}
	constexpr std::size_t total = NumEnums * NumEnums * NumEnums;

	return make_thing3(index, std::make_index_sequence<total>{});
}


int main(void) {
    make_thing3({{A, B, C}})->print();
    make_thing3({{A, A, A}})->print();
    make_thing3({{D, C, B}})->print();
}
