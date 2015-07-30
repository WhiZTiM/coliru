#include <vector>
#include <iostream>

// code taken from 
template<class InputIt1, class InputIt2, class BinaryFunction>
BinaryFunction for_each(InputIt1 first1, InputIt1 last1, InputIt2 first2, BinaryFunction f)
{
    for (; first1 != last1; ++first1, ++first2) {
        f(*first1, *first2);
    }
    return f;
}

struct Foo
{
    Foo() : k(-1){}
	int k;
	void func(int i){k=i;}
};

int main() {
	
	std::vector<Foo> foo(5);
	std::vector<int> bar(5,55);
    
    for_each(foo.begin(), foo.end(), bar.begin(), [](auto& a, const auto& b){a.func(b); return a;});
  
	for(auto f : foo)
	{
		std::cout << f.k << std::endl;
	}
	return 0;
}