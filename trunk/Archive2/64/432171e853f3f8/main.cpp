
#include <iostream>  
#include <utility>
#include <type_traits> 
#include <tuple>
using namespace std; 
 
struct Signature  
{
    struct A 
	{
		const ostream& operator<< (const ostream& streamReceiver)
		{
			return streamReceiver;
		}
	};
 
	struct B
	{
		const ostream& operator<< (const ostream& streamReceiver )
		{
			return streamReceiver ;
		}
	};
 
	tuple<A, B> children = {  make_tuple  (A(),B())   };
};
 

template<typename S, typename T, std::size_t... I>
void print_tuple_like(S& s, const T& t, std::index_sequence<I...>)
{
	void* unused[] = { &(s << std::get<I>(t))... };
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

