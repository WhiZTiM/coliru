#include <iostream>  
#include <utility>
#include <type_traits> 
#include <tuple>
using namespace std; 
 
struct Signature  
{
    struct A 
	{
		friend ostream& operator<<(ostream& os, const A& streamReceiver)
		{
			return os;
		}
	};
 
	struct B
	{
		friend ostream& operator<< (ostream& os, const B& streamReceiver )
		{
			return os;
		}
	};
 
	tuple<A, B> children = {  make_tuple  (A(),B())   };
};
 

template<typename S, typename T, std::size_t... I>
void print_tuple_like(S& s, const T& t, std::index_sequence<I...>)
{
	void* unused[] = { &(s << std::get<I>(t))... };
    (void)unused;
}

template<typename S, typename T,std::size_t N = std::tuple_size<decltype(T::children)>::value>
	S& operator<<(S& s, const T& t)
{
	print_tuple_like(s, t.children, std::make_index_sequence<N>{});
	return s;
}

int main(int argc, char* argv[])
{
	Signature s;
 	cout << s ;

	return 0;
};

