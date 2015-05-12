#include <iostream>
#include <cstdint>
#include <iterator>
#include <array>
#include <vector>
#include <sstream>
#include <functional>


#include <chrono>
#include <cassert>

#include <boost/fusion/include/adapt_struct.hpp> 
#include <boost/fusion/include/begin.hpp>
#include <boost/fusion/include/deref.hpp>
#include <boost/fusion/include/distance.hpp>
#include <boost/fusion/include/end.hpp>
#include <boost/fusion/include/next.hpp>
#include <boost/fusion/include/for_each.hpp>

#include <boost/mpl/bool.hpp>

/*******************************************************************************************/

typedef uint16_t column_id_t;

// Column types
typedef std::string             string_t;
typedef int64_t                 signed_int_t;
typedef uint64_t                unsigned_int_t;
typedef std::array<uint8_t, 6>  mac_address_t;
typedef std::array<uint8_t, 16> scenes_t;
typedef std::vector<uint8_t>    data_t;

struct DeviceTableRow
{
    enum class IDs : column_id_t
    {
        device_address  = 0x00, 
        scenes          = 0x01, 
        label           = 0x02,
        location        = 0x03,
    };

    unsigned_int_t device_address;
    scenes_t scenes;
    string_t label;
    string_t location;
    data_t test_data;
    unsigned_int_t device_type;
};

BOOST_FUSION_ADAPT_STRUCT(
        DeviceTableRow,
        (unsigned_int_t, device_address)
        (scenes_t, scenes)
        (string_t, label)
        (string_t, location)
        (data_t, test_data)
        (unsigned_int_t, device_type)
)

/*******************************************************************************************/

// New search method

template<typename RandomAccessIter>
class DeserializeColumn
{
public:
    DeserializeColumn(
            RandomAccessIter start_range_,
            RandomAccessIter end_range_) 
            : start_range(start_range_)
            , end_range(end_range_)
    {
        typedef typename std::iterator_traits<RandomAccessIter>::iterator_category iter_category_t;
        static_assert(
                std::is_base_of<iter_category_t, std::random_access_iterator_tag>::value, 
                "DeserialiseColumn only accepts iterators with traits of RandomAccessIterator."
        );
    }
    
    template<typename T>
    void operator()(T& table_column)
    {
        Deserialize(table_column);
    }

private:
    RandomAccessIter start_range;
    RandomAccessIter end_range;

    void Deserialize(signed_int_t& x)
    {
        if ((start_range + 8) < end_range)
        {
            // Range is too large to store in an int64_t
            throw std::exception();
        }

        // TODO: Check signed bit and set accordingly (if negative, set x = -1, else set x = 0)

        x = 0;

        for (unsigned int i = 0; start_range != end_range; ++i, ++start_range)
        {
            x = (x << (8 * i)) | (*start_range & UINT8_MAX);
        }
    }

    void Deserialize(string_t& x)
    {
        std::stringstream string_buf;

        for (; start_range != end_range; ++start_range)
        {
            string_buf << *start_range;
        }

        x.assign(string_buf.str());
    }

    void Deserialize(unsigned_int_t& x)
    {
        if ((start_range + 8) < end_range)
        {
            // Range is too large to store in an uint64_t
            throw std::exception();
        }

        x = 0;

        for (unsigned int i = 0; start_range != end_range; ++i, ++start_range)
        {
            x = (x << (8 * i)) | (*start_range & UINT8_MAX);
        }
    }

    void Deserialize(std::vector<uint8_t>& x)
    {
        for (; start_range != end_range; ++start_range)
        {
            x.push_back(*start_range);
        }
    }

    template<std::size_t N>
    void Deserialize(std::array<uint8_t, N>& x)
    {
        if ((end_range - start_range) != N)
        {
            // Throw that column does not match describe table size
            throw std::exception();
        }

        for (unsigned int i = 0; start_range != end_range; ++i, ++start_range)
        {
            x[i] = *start_range;
        }
    }
};

template <typename ResultHandler>
class ColumnIterator
{
public:
    ColumnIterator(unsigned int column_id_, ResultHandler& result_handler_) 
            : column_id(column_id_)
            , result_handler(result_handler_)
    { }
    
    template <typename TableRow>
    bool FindMember(TableRow& table_row)
    {
        return FindMember(
                boost::fusion::begin(table_row),
                boost::fusion::end(table_row)
        );
    }
    
private:
    unsigned int column_index = 0;
    const unsigned int column_id;
    ResultHandler& result_handler;
    
    template <typename First, typename Last>
    bool FindMember(const First& first, const Last& last)
    {
        int distance = boost::fusion::distance(first, last);
        
        assert(distance > 0);
        
        // Early range check
    	if (column_id >= static_cast<unsigned int>(distance))
        {
            return FindMember(first, last, boost::mpl::true_());
        }
        
        // Start iterating
        return FindMember(first, last, boost::mpl::false_());
    }
    
    template <typename First, typename Last>
    bool FindMember(
            const First& first, 
            const Last& last, 
    		boost::mpl::true_) 
    {
        // End of struct error condition
        return false;
    }
    
    template <typename First, typename Last>
    bool FindMember(
            const First& first, 
        	const Last& last, 
    		boost::mpl::false_)
    {
        // Struct members are found by matching on index
        if (column_index++ == column_id)
        {
            result_handler(boost::fusion::deref(first));
            return true;
        }
        
        typedef typename boost::fusion::result_of::next<First>::type next_t;
            
		return FindMember(
				boost::fusion::next(first), 
				last,
				boost::fusion::result_of::equal_to<next_t, Last>()
		);
    }
};

/*******************************************************************************************/

// Old search method

template<typename InputIter>
class DeserializeColumn2
{
public:
    // TODO: do not use int type
    int column_id;

    InputIter start_range;
    InputIter end_range;

    template<typename T>
    void operator()(T& table_column)
    {
        // Searching for column by matching current iteration against column id
        if (column_pos++ == column_id)
        {
            this->Deserialize(table_column);
            deserialize = true;
        }

        if (!deserialize && (column_pos > column_id))
        {
            // Throw as column does not exist
            throw std::exception();
        }
    }

private:
    int column_pos = 0;
    bool deserialize = false;

    void Deserialize(signed_int_t& x)
    {
        if ((start_range + 8) < end_range)
        {
            // Range is too large to store in an int64_t
            throw std::exception();
        }

        // TODO: Check signed bit and set accordingly (if negative, set x = -1, else set x = 0)

        x = 0;

        for (unsigned int i = 0; start_range != end_range; ++i, ++start_range)
        {
            x = (x << (8 * i)) | (*start_range & UINT8_MAX);
        }
    }

    void Deserialize(string_t& x)
    {
        std::stringstream string_buf;

        for (; start_range != end_range; ++start_range)
        {
            string_buf << *start_range;
        }

        x.assign(string_buf.str());
    }

    void Deserialize(unsigned_int_t& x)
    {
        if ((start_range + 8) < end_range)
        {
            // Range is too large to store in an uint64_t
            throw std::exception();
        }

        x = 0;

        for (unsigned int i = 0; start_range != end_range; ++i, ++start_range)
        {
            x = (x << (8 * i)) | (*start_range & UINT8_MAX);
        }
    }

    void Deserialize(std::vector<uint8_t>& x)
    {
        for (; start_range != end_range; ++start_range)
        {
            x.push_back(*start_range);
        }
    }

    template<std::size_t N>
    void Deserialize(std::array<uint8_t, N>& x)
    {
        if ((end_range - start_range) != N)
        {
            // Throw that column does not match describe table size
            throw std::exception();
        }

        for (unsigned int i = 0; start_range != end_range; ++i, ++start_range)
        {
            x[i] = *start_range;
        }
    }
};
    
/*******************************************************************************************/

void NewSearch(
        int column_id, 
        DeviceTableRow& device_table_row, 
        std::vector<uint8_t>::const_iterator beg_, 
        std::vector<uint8_t>::const_iterator end_ )
{
    typedef DeserializeColumn<std::vector<uint8_t>::const_iterator> handler_t;
    
    for (unsigned int i = 0; i < 100000; i++)
    {
        handler_t deserialiser(beg_, end_);
    
        ColumnIterator<handler_t> iter(column_id, deserialiser);
    
        assert(iter.FindMember(device_table_row));
    }
}

void OldSearch(
        int column_id, 
        DeviceTableRow& device_table_row, 
        std::vector<uint8_t>::const_iterator beg_, 
        std::vector<uint8_t>::const_iterator end_ )
{
    typedef DeserializeColumn2<std::vector<uint8_t>::const_iterator> handler2_t;
    
    for (unsigned int i = 0; i < 100000; i++)
    {
        handler2_t deserialize_handler;
        
        deserialize_handler.start_range = beg_;
        deserialize_handler.end_range = end_;
        
        deserialize_handler.column_id = column_id;
        
        boost::fusion::for_each(device_table_row, std::ref(deserialize_handler));
    }
}

void BenchmarkColumnSearch(int column_id)
{
    std::vector<uint8_t> payload = {1,2,3,4};
    
    std::vector<uint8_t>::const_iterator beg_ = std::begin(payload);
    std::vector<uint8_t>::const_iterator end_ = std::end(payload);
    
    {
        // New search method benchmarking
        
        DeviceTableRow device_table_row_new;
        
        auto new_start = std::chrono::high_resolution_clock::now();
        
        NewSearch(column_id, device_table_row_new, beg_, end_);
        
        auto new_end = std::chrono::high_resolution_clock::now();
        
        std::cout << "New: " << std::chrono::duration<double, std::milli>(new_end-new_start).count() << " ms\n";
    }
    
    {
        // Old search method benchmarking
        
        DeviceTableRow device_table_row_old;
        
        auto old_start = std::chrono::high_resolution_clock::now();
        
        OldSearch(column_id, device_table_row_old, beg_, end_);
        
        auto old_end = std::chrono::high_resolution_clock::now();
        
        std::cout << "Old: " << std::chrono::duration<double, std::milli>(old_end-old_start).count() << " ms\n";
    }
}
    
int main(void) 
{
    BenchmarkColumnSearch(0);
    BenchmarkColumnSearch(5);
}
