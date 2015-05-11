#include <iostream>

#include <boost/fusion/include/adapt_struct.hpp> 
#include <boost/fusion/include/begin.hpp>
#include <boost/fusion/include/end.hpp>
#include <boost/fusion/include/next.hpp>

#include <boost/mpl/bool.hpp>

class GetColumnSize
{
public:
    GetColumnSize(column_id_t const column_id) : column_id(column_id)
    { }

    // TODO: do not use int type
    column_id_t const column_id;
    uint64_t column_length = 0;

    template<typename T>
    void operator()(T const& table_column)
    {
        // Searching for column by matching current iteration against column id
        if (this->column_pos++ == this->column_id)
        {
            this->GetSize(table_column);
            this->found = true;
        }

        if (!this->found && (this->column_pos > this->column_id))
        {
            // Throw as column does not exist
            throw std::exception();
        }
    }

private:
    unsigned int column_pos = 0;
    bool found = false;

    uint32_t HighestSetBit(unsigned_int_t n) const
    {
        // TODO: explain
        unsigned_int_t r = 1;

        while (n >>= 1)
        {
            r++;
        }

        return r;
    }

    void GetSize(signed_int_t const& x)
    {
        unsigned_int_t absolute = std::abs(x);
        // TODO: explain
        this->column_length = std::ceil((HighestSetBit(absolute) + 1) / 8.0);
    }

    void GetSize(string_t const& x)
    {
        this->column_length = x.length();
    }

    void GetSize(unsigned_int_t const& x)
    {
        // TODO: explain
        this->column_length = std::ceil((HighestSetBit(x)) / 8.0);
    }

    void GetSize(std::vector<uint8_t> const& x)
    {
        this->column_length = x.size();
    }

    template<std::size_t N>
    void GetSize(std::array<uint8_t, N> const& x)
    {
        this->column_length = N;
    }
};

template <typename First, typename Last>
inline void
print_each_member_name(
        const First& first, 
    	const Last& last, 
		boost::mpl::true_) 
{
    throw std::exception();
}

template <typename First, typename Last>
inline void
print_each_member_name(
        const First& first, 
		const Last& last, 
		boost::mpl::false_)
{
		std::cout << boost::fusion::extension::struct_member_name<typename First::seq_type,
			First::index::value>::call() << std::endl;

		print_each_member_name(
				boost::fusion::next(first), 
				last, 
				boost::fusion::result_of::equal_to<
						typename boost::fusion::result_of::next<First>::type, Last>()
		);
}

namespace ns {
	struct point {
		int x;
		int y;
		int z;
	};
}

BOOST_FUSION_ADAPT_STRUCT(ns::point,
		(int, x)
		(int, y)
		(int, z))

int main(void) {
	
	ns::point mypoint;

	print_each_member_name(
			boost::fusion::begin(mypoint),
			boost::fusion::end(mypoint),
			boost::mpl::false_());

}

