#include <algorithm>
#include <iterator>

namespace container
{
	template<class C>
	class back_overwrite_insert_iterator
		: public std::iterator<std::output_iterator_tag, void, void, void, void>
	{
	public:
		explicit back_overwrite_insert_iterator(C& cont)
			: container{cont}, iter{cont.begin()}, initial_size{cont.size()}
		{
		}
		
		auto& operator++()
		{
			return *this;
		}
		
		auto& operator++(int)
		{
			return *this;
		}
		
		auto& operator*()
		{
			return *this;
		}
		
		auto& operator=(const typename C::value_type& value)
		{
			if(current_size++ < initial_size)
				*iter++ = value;
			else
				container.push_back(value);
			return *this;
		}
		
		auto& operator=(typename C::value_type&& value)
		{
			if(current_size++ < initial_size)
				*iter++ = std::move(value);
			else
				container.push_back(std::move(value));
			return *this;
		}
		
	private:
		C& container;
		typename C::iterator iter;
		typename C::size_type initial_size;
		typename C::size_type current_size {};
	};

	template<class C>
	auto back_overwrite_inserter(C& container)
	{
		return back_overwrite_insert_iterator<C>{container};
	}
	
	template<class C, class I>
	void copy_impl(std::remove_reference_t<C>&& container, I iter)
	{
		std::copy(std::make_move_iterator(begin(container)), 
			std::make_move_iterator(end(container)), iter);
	}
	
	template<class C, class I>
	void copy_impl(const std::remove_reference_t<C>& container, I iter)
	{
		std::copy(begin(container), 
			end(container), iter);
	}
	
	template<class C, class I>
	void copy(C&& container, I iter)
	{
		copy_impl<C>(std::forward<C>(container), iter);
	}
}

#include <iostream>
#include <list>
#include <vector>

int main()
{
	std::vector<int> v{1, 2, 3};
	
	std::copy(v.begin(), v.end(), std::ostream_iterator<int>{std::cout, " "});
	std::cout << '\n';
	
	container::copy(std::vector<int>{5, 6, 7, 8, 9, 0}, 
		container::back_overwrite_inserter(v));
	
	std::copy(v.begin(), v.end(), std::ostream_iterator<int>{std::cout, " "});
	std::cout << '\n';
}