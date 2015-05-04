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

#include <boost/fusion/include/adapt_struct.hpp>
#include <boost/fusion/include/algorithm.hpp>
#include <boost/fusion/include/zip.hpp>

// Sizes
static const uint8_t single_commit_counter_size = 2;
static const uint8_t all_commit_counter_size    = 4;
static const uint8_t commit_counter_count       = 2;

// Column types
typedef std::string             string_t;
typedef int32_t                 int_t;
typedef std::array<uint8_t, 6>  mac_address_t;
typedef std::array<uint8_t, 16> scenes_t;

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
    int_t device_address;
    scenes_t scenes;
    string_t label;
    string_t location;
};

BOOST_FUSION_ADAPT_STRUCT(
        DeviceTableRow,
        (int_t, device_address)
        (scenes_t, scenes)
        (string_t, label)
        (string_t, location)
)

struct DeviceTable
{
    DescribeTable table_info;
    std::map<row_id_t, DeviceTableRow> rows;
};

/**************************************************************************************/

struct WLANTableRow
{
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

class DeviceModel
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
    
    void Deserialize(int& x)
    {
        std::cout << "int const& x" << std::endl;
        
        if ((start_range + 4) < end_range)
        {
            // Range is too large to store in an int
            throw std::exception();
        }
        
        x = 0;
        
        for (unsigned int i = 0; start_range != end_range; ++i, ++start_range)
        {
            x = (x << (8 * i)) | (*start_range & UINT8_MAX);
        }
    }
    
    void Deserialize(std::string& x)
    {
        std::cout << "std::string const& x" << std::endl;
        
        std::stringstream string_buf;
        
        for (; start_range != end_range; ++start_range)
        {
            string_buf << *start_range;
        }
        
        x.assign(string_buf.str());
    }
    
    void Deserialize(uint8_t& x)
    {
        std::cout << "uint8_t const& x" << std::endl;
        
        if ((start_range + 1) > end_range)
        {
            // Throw that column does not match describe table size
            throw std::exception();
        }
        
        x = *start_range;
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
    }
}

// Deserializes the rows based on the row filter and defined row count
template<typename T>
void Deserialize(T& table_map, Filters filters, payload_iter_t& current, payload_iter_t& end)
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
        //throw std::exception();
    }
}

// Deserializes the commit counter into the given table struct
template<typename T>
void Deserialize(T& table_map, payload_iter_t& current, payload_iter_t& end)
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
void Deserialize(T& table_map, Filters filters, std::vector<uint8_t>& payload, bool commit_counter)
{
    payload_iter_t payload_pos = std::begin(payload);
    payload_iter_t payload_end = std::end(payload);
    
    if (commit_counter)
    {
        Deserialize(table_map, payload_pos, payload_end);
    }
    
    Deserialize(table_map, filters, payload_pos, payload_end);
}

// Need to deserialize table based on number of rows, number of columns, 



int main()
{
    // Example payload contains a single row of device table
    std::vector<uint8_t> payload = {
            1,2,3,4,                                    // Commit counters [0] = 0x0102, [1] = 0x0304
            0,5,                                        // Device address
            16,15,14,13,12,11,10,9,8,7,6,5,4,3,2,1,     // Scenes
            'a','y','y','y','y','y','\0',               // Label (early null terminator)
            'b','a','y','b','a','a','y','y',            // Location (exact column length)
    };
    
    DeviceModel device_model;
    
    // Example settings provided by describe table response
    device_model.device_table.table_info = DescribeTable{
            32,         // row count
            {0, 0},     // initial commit counters, should get updated after deserialization
            {
                ColumnInfo{0, 2, ColumnType::UNSIGNED_INT}, // Device address id + length + type
                ColumnInfo{1, 16, ColumnType::BYTE_ARRAY},  // Scenes id + length + type
                ColumnInfo{2, 32, ColumnType::STRING},      // Label id + length + type
                ColumnInfo{3, 8, ColumnType::STRING},       // Location id + length + type
            },
    };
    
    // Example addition of a row
    device_model.device_table.rows[0] = 
            DeviceTableRow{
                    1, 
                    {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16},
                    "abc", 
                    "def"
            };
    
    // Example deserialization. Requires a "table" to output to, the filters specified which generated the data,
    // the actual payload, and whether the commit counter flag was set.
    Deserialize(
            device_model.device_table, 
            Filters{
                    ColumnFilter::ALL_COLUMNS,      // Set the column filter to all columns.
                    static_cast<RowFilter>(1)       // Row filter is chosen by instead casting to a row ID
            },
            payload,
            true
    );
    
    assert(0x0102 == device_model.device_table.table_info.commit_counters[0]);
    assert(0x0304 == device_model.device_table.table_info.commit_counters[1]);
    
    std::cout << "\n\nResults: \n"
            << "device_address: " << device_model.device_table.rows[1].device_address << "\n"
            << "scenes: ";
    std::copy(
            std::begin(device_model.device_table.rows[1].scenes),
            std::end(device_model.device_table.rows[1].scenes),
            std::ostream_iterator<int>(std::cout,",")
     );
     std::cout << "\n"
            << "label: " << device_model.device_table.rows[1].label << "\n"
            << "location: " << device_model.device_table.rows[1].location << "\n";
}
