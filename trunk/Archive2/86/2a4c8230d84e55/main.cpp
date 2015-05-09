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
template <typename C>
class back_insert_constrained_iterator
    : public std::back_insert_iterator<C>
{
public:
	explicit back_insert_constrained_iterator(C& container, unsigned int n)
		: std::back_insert_iterator<C>(container)
        , limit(n)
		, invocations(0)
	{}
	
	back_insert_constrained_iterator& operator=(const typename C::value_type& val) {
		if (++invocations > limit)
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
    const unsigned int limit;
	unsigned int invocations;
};

/**
 * Similar to std::back_inserter; convenience function template that
 * constructs a %back_insert_constrained_iterator.
 */
template <typename C>
back_insert_constrained_iterator<C> back_inserter_constrained(C& c, const unsigned int n)
{
	return back_insert_constrained_iterator<C>(c, n);
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
        detail::back_inserter_constrained(str1, 6)
    );
    std::cout << str1 << std::endl;
    
    // Emit "abcdef"  (char count <  limit)
    std::stringstream ss2("abcdef");
    std::string str2;
    std::copy(
        std::istream_iterator<char>(ss2),
        std::istream_iterator<char>(),
        detail::back_inserter_constrained(str2, 7)
    );
    std::cout << str2 << std::endl;
    
    // Throw          (char count >  limit)
    std::stringstream ss3("abcdef");
    std::string str3;
    std::copy(
        std::istream_iterator<char>(ss3),
        std::istream_iterator<char>(),
        detail::back_inserter_constrained(str3, 5)
    );
    std::cout << str3 << std::endl;
}
