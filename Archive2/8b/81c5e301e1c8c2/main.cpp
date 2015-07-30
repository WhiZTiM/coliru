#include <algorithm>
#include <vector>
#include <iostream>

#include <boost/iterator/zip_iterator.hpp>

struct Foo
{
    Foo() : k(-1){}
	int k;
	void func(int i){k=i;}
};

int main() {
	
	std::vector<Foo> foo(5);
	std::vector<int> bar(5,55);
    
	auto zip_func = [](auto&& t){t.template get<0>().func(t.template get<1>());};
	std::for_each(
        boost::make_zip_iterator(
            boost::make_tuple(foo.begin(), bar.begin())
        ),
        boost::make_zip_iterator(
            boost::make_tuple(foo.end(), bar.end())
       ),
       zip_func
    );
  
	for(auto f : foo)
	{
		std::cout << f.k << std::endl;
	}
	return 0;
}