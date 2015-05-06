#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <map>
#include <functional>
#include <array>
#include <cstdint>
#include <iterator>
#include <cassert>
#include <cmath>
#include <cstdlib>

#include <boost/fusion/include/adapt_struct.hpp>
#include <boost/fusion/include/algorithm.hpp>
#include <boost/fusion/include/zip.hpp>

// Sizes
static const uint8_t single_commit_counter_size = 2;
static const uint8_t all_commit_counter_size    = 4;
static const uint8_t commit_counter_count       = 2;

// Column types
typedef std::string             string_t;
typedef int64_t                 signed_int_t;
typedef uint64_t                unsigned_int_t;
typedef std::array<uint8_t, 6>  mac_address_t;
typedef std::array<uint8_t, 16> scenes_t;
typedef std::vector<uint8_t>    data_t;

// Other
typedef uint16_t                        column_id_t;
typedef uint16_t                        row_id_t;
typedef uint8_t                         table_id_t;
typedef std::vector<uint8_t>::iterator  payload_iter_t;
typedef std::array<uint16_t, 2>         commit_counters_t;

/**************************************************************************************/

// These enums will be defined in database payload

enum class ColumnFilter : column_id_t
{
    ALL_COLUMNS = 0x1FFF,
};

enum class RowFilter : row_id_t
{
    ALL_ROWS = 0xFFFF,
};

/**************************************************************************************/

// These will be defined in types

struct Filters
{
    ColumnFilter column_filter;
    RowFilter row_filter;
};

enum class ColumnType : uint8_t
{
    UNSIGNED_INT        = 0x01,
    INT                 = 0x02,
    BIT_FIELD           = 0x03,
    TIME                = 0x04,
    STRING              = 0x05,
    BYTE_ARRAY          = 0x06,
    UNSIGNED_INT_ARRAY  = 0x07,
    DATA                = 0x08,
};

// Describe table response
struct ColumnInfo
{
    typedef uint16_t column_length_t;
    
    column_id_t     id;
    column_length_t length;
    ColumnType      type;
};

struct DescribeTable
{
    typedef std::vector<ColumnInfo> column_info_t;
    
    uint32_t            row_count;
    commit_counters_t   commit_counters;
    column_info_t       column_info;
};

// Show tables response
struct TableInfo
{
    typedef std::array<uint8_t, 2> table_version_t;
    
    table_id_t      id;
    table_version_t version;
};

struct ShowTables
{
    TableInfo table_info;
};

// Table status response
struct TableStatusInfo
{
    table_id_t          id;
    commit_counters_t   commit_counters;
};

struct TableStatus
{
    typedef std::vector<TableStatusInfo> table_status_t;
    
    table_status_t table_status;
};

/**************************************************************************************/

// These table structs will be auto generated from python script based on what is in schema database

struct DeviceTableRow
{
    enum class IDs : column_id_t
    {
        device_address  = 0x00, 
        scenes          = 0x01, 
        label           = 0x02,
        location        = 0x03,
    };
    
    signed_int_t device_address;
    scenes_t scenes;
    string_t label;
    string_t location;
    data_t test_data;
    unsigned_int_t device_type;
};

BOOST_FUSION_ADAPT_STRUCT(
        DeviceTableRow,
        (signed_int_t, device_address)
        (scenes_t, scenes)
        (string_t, label)
        (string_t, location)
        (data_t, test_data)
        (unsigned_int_t, device_type)
)

struct DeviceTable
{
    DescribeTable table_info;
    std::map<row_id_t, DeviceTableRow> rows;
};

/**************************************************************************************/

struct WLANTableRow
{
    enum class IDs : column_id_t
    {
        mac_address = 0x00,
        ssid        = 0x01,
        password    = 0x02,
    };
    
    mac_address_t mac_address;
    std::string ssid;
    std::string password;
};

BOOST_FUSION_ADAPT_STRUCT(
        WLANTableRow,
        (mac_address_t, mac_address)
        (string_t, ssid)
        (string_t, password)
)

struct WLANTable
{
    DescribeTable table_info;
    std::map<row_id_t, WLANTableRow> rows;
};

/**************************************************************************************/

class DataModel
{
public:
    DeviceTable device_table;
    WLANTable wlan_table;
    
private:
     
    
    // Will have methods for committing a table row to remote or local database
    // and synchronizing from both sources
};

/**************************************************************************************/

// Following are the deserialize functions. Can be passed any of the table structs to deserialize into.

// Deserializes a column from the payload into the given table struct. How it works is a reference to
// a column within the struct is passed via the operator(). The payload is read and deserialized into
// the given type. Column params such as length is defined by column_length, and the actual type is
// determined depending on the overload of Deserialize.
class DeserializeColumn
{
public:
    // TODO: do not use int type
    int column_id;
    
    payload_iter_t start_range;
    payload_iter_t end_range;
    
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
        std::cout << "signed_int_t const& x" << std::endl;
        
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
        std::cout << "string_t const& x" << std::endl;
        
        std::stringstream string_buf;
        
        for (; start_range != end_range; ++start_range)
        {
            string_buf << *start_range;
        }
        
        x.assign(string_buf.str());
    }
    
    void Deserialize(unsigned_int_t& x)
    {
        std::cout << "unsigned_int_t const& x" << std::endl;
        
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
        std::cout << "std::vector<uint8_t> const& x" << std::endl;
        
        for (; start_range != end_range; ++start_range)
        {
            x.push_back(*start_range);
        }
    }
    
    template<std::size_t N>
    void Deserialize(std::array<uint8_t, N>& x)
    {
        std::cout << "std::array<uint8_t, " << N << "> const& x" << std::endl;
        
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

void GetFixedByteRange(
    ColumnInfo::column_length_t length,
    payload_iter_t& current_pos,
    payload_iter_t const& end_pos,
    payload_iter_t& start_range_out,
    payload_iter_t& end_range_out )
{
    if ((current_pos + length) > end_pos)
    {
        // Payload doesn't have enough bytes left to contain current column
        throw std::exception();
    }
    
    // Set the byte range
    start_range_out = current_pos;
    end_range_out = current_pos + length;
    
    // Update current position to end of byte range
    current_pos += length;
}

void GetDataByteRange(
    ColumnInfo::column_length_t const& length,
    payload_iter_t& current_pos,
    payload_iter_t const& end_pos,
    payload_iter_t& start_range_out,
    payload_iter_t& end_range_out )
{
    if ((current_pos + 2) > end_pos)
    {
        // Payload doesn't have enough bytes to contain length prefix
        throw std::exception();
    }
    
    // Length prefix is the first two bytes, big endian
    uint16_t length_prefix = *(current_pos++);
    length_prefix = (length_prefix << 8) | (*(current_pos++) & UINT8_MAX);
    
    if ((current_pos + length_prefix) > end_pos)
    {
        // Payload doesn't have enough bytes left to contain current column
        throw std::exception();
    }
    
    // Set the byte range
    start_range_out = current_pos;
    end_range_out = current_pos + length_prefix;
    
    // Update current position to end of byte range
    current_pos += length_prefix;
}

void GetStringByteRange(
    ColumnInfo::column_length_t const& length,
    payload_iter_t& current_pos,
    payload_iter_t const& end_pos,
    payload_iter_t& start_range_out,
    payload_iter_t& end_range_out )
{
    // Need a copy of current position so that we still have a reference to beginning
    payload_iter_t temp_current_pos = current_pos;
    
    // Strings can end early using a string delimiter ('\0') or are up to the length
    // as returned by describe table.
    for (unsigned int i = 0; i < length; i++, temp_current_pos++)
    {
        if (temp_current_pos > end_pos)
        {
            // Payload doesn't have enough bytes left to contain current column
            throw std::exception();
        }
        
        if (*temp_current_pos == '\0')
        {
            temp_current_pos++;
            break;
        }
    }
    
    // Set the byte range
    start_range_out = current_pos;
    end_range_out = temp_current_pos;
    
    // Update current position to end of byte range
    current_pos = temp_current_pos;
}

void GetColumnBytes(
        ColumnInfo::column_length_t const& length,
        ColumnType const& type,
        payload_iter_t& current_pos,
        payload_iter_t const& end_pos,
        payload_iter_t& start_range_out,
        payload_iter_t& end_range_out )
{
    switch (type)
    {
    case ColumnType::STRING:
        GetStringByteRange(
                length, 
                current_pos, 
                end_pos, 
                start_range_out, 
                end_range_out
        );
        break;
        
    case ColumnType::DATA:
        GetDataByteRange(
                length, 
                current_pos, 
                end_pos, 
                start_range_out, 
                end_range_out
        );
        break;
        
    default:
        GetFixedByteRange(
                length, 
                current_pos, 
                end_pos, 
                start_range_out, 
                end_range_out
        );
        break;
    }
}

// Calls the method for deserializing column into given table struct
template<typename T>
void Deserialize(
        T& table, 
        ColumnInfo const& column_info_entry, 
        payload_iter_t& current, 
        payload_iter_t const& end )
{
    DeserializeColumn deserialize_handler;
            
    GetColumnBytes(
            column_info_entry.length,
            column_info_entry.type,
            current,
            end,
            deserialize_handler.start_range,
            deserialize_handler.end_range
    );
    
    deserialize_handler.column_id = column_info_entry.id;
    
    boost::fusion::for_each(table, std::ref(deserialize_handler));
}

// Deserializes based on column filter and current column layout as defined within describe table
template<typename T>
void Deserialize(
        T& table, 
        DescribeTable::column_info_t const& column_info, 
        ColumnFilter const& column_filter, 
        payload_iter_t& current, 
        payload_iter_t const& end )
{
    if (column_filter == ColumnFilter::ALL_COLUMNS)
    {
        for (ColumnInfo const& column_info_entry : column_info)
        {
            Deserialize(table, column_info_entry, current, end);
        }
    }
    else
    {
        for (ColumnInfo const& column_info_entry : column_info)
        {
            if (column_info_entry.id == static_cast<column_id_t>(column_filter))
            {
                Deserialize(table, column_info_entry, current, end);
                return;
            }
        }
        
        // Column id was not found
        throw std::exception();
    }
}

// Deserializes the rows based on the row filter and defined row count
template<typename T>
void Deserialize(T& table_map, Filters const& filters, payload_iter_t& current, payload_iter_t const& end)
{
    // Iterate over rows depending on filter
    // Try to deserialize each row
    if (filters.row_filter == RowFilter::ALL_ROWS)
    {
        table_map.rows.clear();
        
        for (unsigned int i = 0; i < table_map.table_info.row_count; i++)
        {
            Deserialize(
                    table_map.rows[i], 
                    table_map.table_info.column_info, 
                    filters.column_filter, 
                    current, 
                    end
            );
        }
    }
    else if (static_cast<row_id_t>(filters.row_filter) > table_map.table_info.row_count)
    {
        // Row id is outside table size
        throw std::exception();
    }
    else
    {
        // Deserialize into row ID
        Deserialize(
                table_map.rows[static_cast<row_id_t>(filters.row_filter)], 
                table_map.table_info.column_info, 
                filters.column_filter, 
                current, 
                end
        );
    }
    
    if (current != end)
    {
        // Still extra bytes left in payload
        throw std::exception();
    }
}

// Deserializes the commit counter into the given table struct
template<typename T>
void Deserialize(T& table_map, payload_iter_t& current, payload_iter_t const& end)
{
    if ((current + all_commit_counter_size) > end)
    {
        // Isn't long enough to contain commit counter, throw error
        throw std::exception();
    }
    
    for (unsigned int i = 0; i < commit_counter_count; i++)
    {
        uint16_t commit_counter = *(current++);
        commit_counter = (commit_counter << 8) | (*(current++) & UINT8_MAX);
        table_map.table_info.commit_counters[i] = commit_counter;
    }
}

template<typename T>
void Deserialize(T& table_map, Filters const& filters, payload_iter_t& current, payload_iter_t const& end, bool const& commit_counter)
{
    if (commit_counter)
    {
        Deserialize(table_map, current, end);
    }
    
    Deserialize(table_map, filters, current, end);
}

template<typename T>
void Deserialize(T& table_map, Filters const& filters, std::vector<uint8_t>& payload, bool const& commit_counter)
{
    payload_iter_t payload_pos = std::begin(payload);
    payload_iter_t payload_end = std::end(payload);
    
    Deserialize(table_map, filters, payload_pos, payload_end, commit_counter);
}

/**************************************************************************************/

// Following is serialization methods

// Calculates the row size based on column filter
uint64_t CalculateRowSize(ColumnFilter const& column_filter, DescribeTable::column_info_t const& column_info)
{
    // If filter == ALL_COLUMNS iterate through all columns and add lengths
    if (column_filter == ColumnFilter::ALL_COLUMNS)
    {
        uint64_t row_size = 0;
        
        for (ColumnInfo const& column_info_entry : column_info)
        {
            row_size += column_info_entry.length;
        }
        
        return row_size;
    }
    
    // Else try and find the column id and return the columns length
    for (ColumnInfo const& column_info_entry : column_info)
    {
        if (column_info_entry.id == static_cast<column_id_t>(column_filter))
        {
            return column_info_entry.length;
        }
    }
    
    // Column id was not found
    throw std::exception();
}

// Calculates the minimum size required for serialization
uint64_t CalculateMinimumSize(Filters const& filters, DescribeTable const& table_info)
{
    uint64_t row_size = CalculateRowSize(filters.column_filter, table_info.column_info);
    
    // If row filter == ALL_ROWS, minimum size is no. of rows * row_size
    if (filters.row_filter == RowFilter::ALL_ROWS)
    {
        return table_info.row_count * row_size;
    }
    
    // Return a single row in size if row exists
    if (table_info.row_count > static_cast<row_id_t>(filters.row_filter))
    {
        return row_size;
    }
    
    // Row does not exist
    throw std::exception();
}

class GetColumnSize
{
public:
    GetColumnSize(column_id_t const column_id) : column_id(column_id)
    {
        
    }

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

template<typename OutputIter>
class SerializeColumn
{
public:
    SerializeColumn(
            OutputIter& output_iter, 
            column_id_t const column_id, 
            ColumnInfo::column_length_t const column_length ) :
            output_iter(output_iter),
            column_id(column_id),
            column_length(column_length)
    {
        
    }
    
    template<typename T>
    void operator()(T const& table_column)
    {
        // Searching for column by matching current iteration against column id
        if (column_pos++ == column_id)
        {
            this->Serialize(table_column);
            serialize = true;
        }
        
        if (!serialize && (column_pos > column_id))
        {
            // Throw as column does not exist
            throw std::exception();
        }
    }
    
private:
    uint32_t column_pos = 0;
    bool serialize = false;
    
    // Serialize into output iterators
    OutputIter& output_iter;
    
    column_id_t const                   column_id;
    ColumnInfo::column_length_t const   column_length;
    
    void Serialize(signed_int_t const& x)
    {
        for (unsigned int i = 0; i < column_length; ++i, ++output_iter)
        {
            *output_iter = x >> (8 * (column_length - i - 1));
        }
    }
    
    void Serialize(string_t const& x)
    {
        for (unsigned int i = 0; i < x.length(); ++i, ++output_iter)
        {
            *output_iter = x[i];
        }
    }
    
    void Serialize(unsigned_int_t const& x)
    {
        for (unsigned int i = 0; i < column_length; ++i, ++output_iter)
        {
            *output_iter = x >> (8 * (column_length - i - 1));
        }
    }
    
    void Serialize(std::vector<uint8_t> const& x)
    {
        for (unsigned int i = 0; i < x.size(); ++i, ++output_iter)
        {
            *output_iter = x[i];
        }
    }
    
    template<std::size_t N>
    void Serialize(std::array<uint8_t, N> const& x)
    {
        for (unsigned int i = 0; i < x.size(); ++i, ++output_iter)
        {
            *output_iter = x[i];
        }
    }
};

template<typename T, typename OutputIter>
void SerializeString(
        T const& table_row, 
        ColumnInfo const& column_info_entry,
        OutputIter& output_iter )
{
    // Get actual size of specified column
    GetColumnSize column_size_handler(column_info_entry.id);
    boost::fusion::for_each(table_row, std::ref(column_size_handler));
    
    uint64_t column_size = column_size_handler.column_length;
    
    // Check column size
    if (column_size > column_info_entry.length)
    {
        throw std::exception();
    }
    
    // Serialize column
    SerializeColumn<OutputIter> serialize_handler(output_iter, column_info_entry.id, column_size);
    boost::fusion::for_each(table_row, std::ref(serialize_handler));
    
    // If the column has smaller length than max, needs a null terminator at end
    if (column_size < column_info_entry.length)
    {
        *output_iter++ = '\0';
    }
}

template<typename T, typename OutputIter>
void SerializeData(
        T const& table_row, 
        ColumnInfo const& column_info_entry,
        OutputIter& output_iter )
{
    // Get actual size of specified column
    GetColumnSize column_size_handler(column_info_entry.id);
    boost::fusion::for_each(table_row, std::ref(column_size_handler));
    
    uint64_t column_size = column_size_handler.column_length;
    
    // Check column size
    if ((column_size + 2) > column_info_entry.length)
    {
        throw std::exception();
    }
    
    // Add length prefix
    *output_iter++ = (uint8_t)(column_size >> 8);
    *output_iter++ = (uint8_t)(column_size);
    
    // Serialize column
    SerializeColumn<OutputIter> serialize_handler(output_iter, column_info_entry.id, column_size);
    boost::fusion::for_each(table_row, std::ref(serialize_handler));
}

template<typename T, typename OutputIter>
void SerializeFixed(
        T const& table_row, 
        ColumnInfo const& column_info_entry,
        OutputIter& output_iter )
{
    // Get actual size of specified column
    GetColumnSize column_size_handler(column_info_entry.id);
    boost::fusion::for_each(table_row, std::ref(column_size_handler));
    
    uint64_t column_size = column_size_handler.column_length;
    
    // Check column size
    if (column_size > column_info_entry.length)
    {
        throw std::exception();
    }
    
    // Serialize column
    SerializeColumn<OutputIter> serialize_handler(output_iter, column_info_entry.id, column_info_entry.length);
    boost::fusion::for_each(table_row, std::ref(serialize_handler));
}

// Calls the method for deserializing column into given table struct
template<typename T, typename OutputIter>
void Serialize(
        T const& table_row, 
        ColumnInfo const& column_info_entry, 
        OutputIter& output_iter )
{
    switch (column_info_entry.type)
    {
    case ColumnType::STRING:
        SerializeString(table_row, column_info_entry, output_iter);
        break;
        
    case ColumnType::DATA:
        SerializeData(table_row, column_info_entry, output_iter);
        break;
        
    default:
        SerializeFixed(table_row, column_info_entry, output_iter);
        break;
    }
}

template<typename T, typename OutputIter>
void Serialize(
        T const& table_row,  
        DescribeTable::column_info_t const& column_info,
        ColumnFilter const& column_filter,
        OutputIter& output_iter )
{
    // Iterate through table column_info member depending on column_filter
    if (column_filter == ColumnFilter::ALL_COLUMNS)
    {
        for (ColumnInfo const& column_info_entry : column_info)
        {
            Serialize(table_row, column_info_entry, output_iter);
        }
    }
    else
    {
        for (ColumnInfo const& column_info_entry : column_info)
        {
            const column_id_t filter = static_cast<column_id_t>(column_filter);
            
            if (column_info_entry.id == filter)
            {
                Serialize(table_row, column_info_entry, output_iter);
                return;
            }
        }
        
        // Column id was not found
        throw std::exception();
    }
}

template<typename T, typename OutputIter>
void Serialize(
        T& table, 
        Filters const& filters, 
        OutputIter& output_iter )
{
    // Iterate through number of rows depending on row_filter and call serialize with specified column filter
    if (filters.row_filter == RowFilter::ALL_ROWS)
    {
        // Serialize all rows
        for (unsigned int i = 0; i < table.table_info.row_count; i++)
        {
            Serialize(
                    table.rows[i], 
                    table.table_info.column_info, 
                    filters.column_filter, 
                    output_iter
            );
        }
    }
    else if (static_cast<row_id_t>(filters.row_filter) > table.table_info.row_count)
    {
        // Row id is outside table size
        throw std::exception();
    }
    else
    {
        // Serialize given row id
        Serialize(
                table.rows[static_cast<row_id_t>(filters.row_filter)], 
                table.table_info.column_info, 
                filters.column_filter, 
                output_iter
        );
    }
}

template<typename OutputIter>
void Serialize(commit_counters_t const& commit_counters, OutputIter& output_iter)
{
    for (unsigned int i = 0; i < commit_counter_count; i++)
    {
        *output_iter++ = (uint8_t)(commit_counters[i] >> 8);
        *output_iter++ = (uint8_t)(commit_counters[i]);
    }
}

template<typename T, typename OutputIter>
void Serialize(
        T& table, 
        Filters const& filters, 
        OutputIter output_iter,
        bool const& commit_counters )
{
    if (commit_counters)
    {
        Serialize(table.table_info.commit_counters, output_iter);
    }
    
    Serialize(table, filters, output_iter);
}

template<typename T>
void Serialize(
        T& table, 
        Filters const& filters, 
        std::vector<uint8_t>& output_payload,
        bool const& commit_counters )
{
    // Automatically reserve's the required space for serialization
    output_payload.reserve(CalculateMinimumSize(filters, table.table_info) + output_payload.size());
    // Provide back_inserter to output_payload
    Serialize(table, filters, std::back_inserter(output_payload), commit_counters);
}

/**************************************************************************************/

// Example usage code

void DeserializeExample()
{
    // Example payload contains a single row of device table
    std::vector<uint8_t> payload = {
            1,2,3,4,                                    // Commit counters [0] = 0x0102, [1] = 0x0304
            0,5,                                        // Device address
            16,15,14,13,12,11,10,9,8,7,6,5,4,3,2,1,     // Scenes
            'a','y','y','y','y','y','\0',               // Label (early null terminator)
            'b','a','y','b','a','a','y','y',            // Location (exact column length)
    };
    
    DataModel data_model;
    
    // Example settings provided by describe table response
    data_model.device_table.table_info = DescribeTable{
            32,         // row count
            {0, 0},     // initial commit counters, should get updated after deserialization
            {
                ColumnInfo{0, 2, ColumnType::UNSIGNED_INT}, // Device address id + length + type
                ColumnInfo{1, 16, ColumnType::BYTE_ARRAY},  // Scenes id + length + type
                ColumnInfo{2, 32, ColumnType::STRING},      // Label id + length + type
                ColumnInfo{3, 8, ColumnType::STRING},       // Location id + length + type
            },
    };
    
    // Example deserialization. Requires a "table" to output to, the filters specified which generated the data,
    // the actual payload, and whether the commit counter flag was set.
    Deserialize(
            data_model.device_table, 
            Filters{
                    ColumnFilter::ALL_COLUMNS,      // Set the column filter to all columns.
                    static_cast<RowFilter>(1)       // Row filter is chosen by instead casting to a row ID
            },
            payload,
            true
    );
    
    assert(0x0102 == data_model.device_table.table_info.commit_counters[0]);
    assert(0x0304 == data_model.device_table.table_info.commit_counters[1]);
    
    std::cout << "\n\nResults: \n"
            << "device_address: " << data_model.device_table.rows[1].device_address << "\n"
            << "scenes: ";
    std::copy(
            std::begin(data_model.device_table.rows[1].scenes),
            std::end(data_model.device_table.rows[1].scenes),
            std::ostream_iterator<int>(std::cout,",")
    );
    std::cout << "\n"
            << "label: " << data_model.device_table.rows[1].label << "\n"
            << "location: " << data_model.device_table.rows[1].location << "\n";
}

void MinimumSizeTests()
{
    DescribeTable table_info = DescribeTable{
            32,
            {0x0103, 0x4512},
            {
                ColumnInfo{0, 2, ColumnType::UNSIGNED_INT},
                ColumnInfo{1, 16, ColumnType::BYTE_ARRAY},
                ColumnInfo{2, 32, ColumnType::STRING},
                ColumnInfo{3, 8, ColumnType::STRING},
            },
    };
    
    Filters filters = Filters{
            ColumnFilter::ALL_COLUMNS,
            static_cast<RowFilter>(31)
    };
    
    assert(58 == CalculateMinimumSize(filters, table_info));
    
    filters = Filters{
            ColumnFilter::ALL_COLUMNS,
            RowFilter::ALL_ROWS
    };
    
    assert(1856 == CalculateMinimumSize(filters, table_info));
    
    filters = Filters{
            static_cast<ColumnFilter>(DeviceTableRow::IDs::scenes),
            RowFilter::ALL_ROWS
    };
    
    assert(512 == CalculateMinimumSize(filters, table_info));
}

void SerializeExample()
{
    DataModel data_model;
    
    data_model.device_table.table_info = DescribeTable{
            32,                 // row count
            {0x0103, 0x4512},   // initial commit counters
            {
                ColumnInfo{0, 2, ColumnType::INT}, // Device address id + length + type
                ColumnInfo{1, 16, ColumnType::BYTE_ARRAY},  // Scenes id + length + type
                ColumnInfo{2, 32, ColumnType::STRING},      // Label id + length + type
                ColumnInfo{3, 8, ColumnType::STRING},       // Location id + length + type
                ColumnInfo{4, 12, ColumnType::DATA},        // Test data id + length + type
                ColumnInfo{5, 1, ColumnType::UNSIGNED_INT}, // Device type id + length + type
            },
    };
    
    Filters filters = Filters{
            ColumnFilter::ALL_COLUMNS,      // Set the column filter to all columns.
            static_cast<RowFilter>(0)       // Row filter is chosen by instead casting to a row ID
    };
    
    assert(71 == CalculateMinimumSize(filters, data_model.device_table.table_info));
    
    // Example addition of a row
    data_model.device_table.rows[0] = 
            DeviceTableRow{
                    -1, 
                    {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16},
                    "abc", 
                    "defghijk",
                    {1,2,3,4},
                    50
            };
    
    std::vector<uint8_t> payload;
    
    // Example serialization. Requires a "table" to get input from including commit counters. The filters specified
    // define which row and which columns to serialize from the table. The boolean specifies whether to include the
    // commit counters when serializing.
    Serialize(
            data_model.device_table, 
            Filters{
                    ColumnFilter::ALL_COLUMNS,      // Set the column filter to all columns.
                    static_cast<RowFilter>(0)       // Row filter is chosen by instead casting to a row ID
            },
            payload,
            true
    );
    
    std::vector<uint8_t> expected = {
            0x01,0x03,0x45,0x12,                    // Commit counters
            255,255,                                // Device address (signed type == -1)
            1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16, // Scenes
            'a','b','c','\0',                       // Label (null terminated)
            'd','e','f','g','h','i','j','k',        // Location (exact length string type)
            0,4,1,2,3,4,                            // Test data (length prefix)
            50,                                     // Device type
    };
    
    assert(payload == expected);
}

int main()
{
    MinimumSizeTests();
    DeserializeExample();
    SerializeExample();
}
