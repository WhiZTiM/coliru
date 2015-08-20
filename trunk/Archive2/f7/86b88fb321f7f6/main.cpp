#include <iostream>
#include <string>
#include <sstream>
#include <unordered_map>
#include <functional>
#include <memory>
#include <type_traits>
#include <utility>
#include <vector>

struct callable {
    virtual void operator()(std::string param_string) const = 0;
	virtual ~callable(){}
};

struct bob {
	std::string s{"hi\n"};
	
	bob() = default;
	bob(bob const&) = default;
	bob& operator=(std::string n) { s = n + " -- assigned\n"; return *this; }
	
	friend std::stringstream& operator>>(std::stringstream& str, bob& b) {
		std::string tmp;
		str >> tmp; 
		b = tmp;
        return str;
	}
	
};


template <typename T>
T gimme(std::stringstream& str) {
	T t;
	str >> t;
	return t;
}


template <typename ...Args>
struct func : callable {
	
	using func_type = void(Args...);
	func_type *ptr{};
	
	constexpr func(func_type* ptr) noexcept : ptr{ptr} {}
	
	template <size_t ...Ns>
	void doit(std::tuple<Args...> const& t, std::index_sequence<Ns...>) const
	{
		(*ptr)( std::get<Ns>(t)... );
	}
	
	void operator()(std::string param_string) const override {
		std::stringstream str{param_string};
		std::tuple<Args...> t{ gimme<Args>(str)... };
		
		doit(t,std::index_sequence_for<Args...>{});
		
	}
};


void blah(int i, char c) { std::cout << "blah -- " << i << "," << c << "\n"; }
void blar(float f) { std::cout << "blar -- " << f << "\n"; }

void dlar(bob b) { std::cout << b.s << "\n"; }


template <typename R, typename...Args>
std::unique_ptr<callable>
make_func(R(*ptr)(Args...)) { 
	return std::make_unique<func<Args...>>(ptr);
}

int main() {
	
	std::vector<std::unique_ptr<callable>> v; 
	v.emplace_back(make_func(&blah));
	//v.emplace_back(make_func(&blar));
	v.emplace_back(make_func(&dlar));
	
	std::vector<std::string> strs;
	strs.emplace_back("1 a"); strs.emplace_back("0.001f");
	
	for (size_t i = 0; i < v.size(); i++) {
		(*v[i])(strs[i]);
	}

}