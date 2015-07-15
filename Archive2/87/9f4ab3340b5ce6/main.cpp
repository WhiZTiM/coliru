#include <range/v3/all.hpp>
#include <iostream>
#include <vector>
struct MyRange
  : ranges::range_facade<MyRange>
{
private:
    friend struct ranges::range_access;
    std::vector<int> ints_;
    
	template <bool isConst>
	struct cursor
    {
    private:
		using It = typename std::conditional<isConst, std::vector<int>::const_iterator, std::vector<int>::iterator>::type;
		using RefType = typename std::conditional<isConst, int const&, int&>::type;
		It iter;
    public:
        cursor() = default;
        cursor(It it)
          : iter(it)
        {}
		RefType current() const
        {
            return *iter;
        }
        bool equal(cursor const &that) const
        {
            return iter == that.iter;
        }
        void next()
        {
            ++iter;
        }
        void prev()
        {
            --iter;
        }
        std::ptrdiff_t distance_to(cursor const &that) const
        {
            return that.iter - iter;
        }
        void advance(std::ptrdiff_t n)
        {
            iter += n;
        }
    };

// Comment out these const overloads and it will work.
    cursor<true> begin_cursor() const
    {
        return {ints_.begin()};
    }
    cursor<true> end_cursor() const
    {
        return {ints_.end()};
    }


    cursor<false> begin_cursor()
    {
        return {ints_.begin()};
    }
    cursor<false> end_cursor()
    {
        return {ints_.end()};
    }

public:
    MyRange()
      : ints_{1, 2, 3, 4, 5, 6, 7}
    {}
};


int main() {
	MyRange nc;
	int& nci = *nc.begin();
    nci = 5;
    std::cout << "non const access ok: " << nci << std::endl; 
}



