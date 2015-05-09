#include <iterator>
#include <sstream>
#include <iostream>

namespace detail {

class back_insert_constraint_failed : public std::exception
{};

/**
 * Wrapper around std::back_insert_iterator that throws
 * %back_insert_constraint_failed when invoked after %N insertions
 * into %C have already been performed through the same instance.
 */
template <typename C, unsigned int N>
class back_insert_constrained_iterator
    : public std::back_insert_iterator<C>
{
public:
	explicit back_insert_constrained_iterator(C& container)
		: std::back_insert_iterator<C>(container)
		, invocations(0)
	{}
	
	back_insert_constrained_iterator& operator=(const typename C::value_type& val) {
		if (++invocations > N)
			throw back_insert_constraint_failed();
		
		return static_cast<back_insert_constrained_iterator&>(std::back_insert_iterator<C>::operator=(val));
	}
	
	back_insert_constrained_iterator& operator*() {
		return static_cast<back_insert_constrained_iterator&>(std::back_insert_iterator<C>::operator*());
	}
	
	back_insert_constrained_iterator& operator++() {
		return static_cast<back_insert_constrained_iterator&>(std::back_insert_iterator<C>::operator++());
	}
	
	back_insert_constrained_iterator& operator++(int) {
		return static_cast<back_insert_constrained_iterator&>(std::back_insert_iterator<C>::operator++(0));
	}

protected:
	C* container;
	
private:
	unsigned int invocations;
};

/**
 * Similar to std::back_inserter; convenience function template that
 * constructs a %back_insert_constrained_iterator.
 */
template <unsigned int N, typename C>
back_insert_constrained_iterator<C, N> back_inserter_constrained(C& c)
{
	return back_insert_constrained_iterator<C, N>(c);
}

}

int main()
{    
    // Emit "abcdef"  (char count == limit)
    std::stringstream ss1("abcdef");
    std::string str1;
    std::copy(
        std::istream_iterator<char>(ss1),
        std::istream_iterator<char>(),
        detail::back_inserter_constrained<6>(str1)
    );
    std::cout << str1 << std::endl;
    
    // Emit "abcdef"  (char count <  limit)
    std::stringstream ss2("abcdef");
    std::string str2;
    std::copy(
        std::istream_iterator<char>(ss2),
        std::istream_iterator<char>(),
        detail::back_inserter_constrained<7>(str2)
    );
    std::cout << str2 << std::endl;
    
    // Throw          (char count >  limit)
    std::stringstream ss3("abcdef");
    std::string str3;
    std::copy(
        std::istream_iterator<char>(ss3),
        std::istream_iterator<char>(),
        detail::back_inserter_constrained<5>(str3)
    );
    std::cout << str3 << std::endl;
}
