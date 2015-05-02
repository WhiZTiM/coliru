#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <functional>
#include <array>
#include <tuple>
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
typedef uint16_t                        row_id_t;
typedef uint16_t                        column_id_t;
typedef uint16_t                        column_length_t;
typedef uint8_t                         column_type_t;
typedef uint8_t                         table_id_t;
typedef std::array<uint16_t, 2>         commit_counters_t;
typedef std::array<uint8_t, 2>          table_version_t;
typedef std::vector<uint8_t>::iterator  payload_iter_t;




typedef std::tuple<column_id_t, column_length_t, column_type_t>     column_info_entry_t;
typedef std::vector<column_info_entry_t>                            column_info_t;
typedef std::tuple<table_id_t, table_version_t>                     table_info_entry_t;
typedef std::vector<table_info_entry_t>                             table_info_t;
typedef std::tuple<table_id_t, commit_counters_t>                   table_status_entry_t;
typedef std::vector<table_status_entry_t>                           table_status_t;

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

struct DescribeTable
{
    uint32_t            row_count;
    commit_counters_t   commit_counters;
    column_info_t       column_info;
};

struct ShowTables
{
    table_info_t table_info;
};

struct TableStatus
{
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
// a column within the struct is passed via the operator().
struct DeserializeColumn
{
    int column_pos;
    int column_id;
    int column_length;
    
    payload_iter_t current_pos;
    payload_iter_t end_pos;
    
    bool deserialized = false;
    
    template<std::size_t N>
    void Deserialize(std::array<uint8_t, N> const& x)
    {
        std::cout << "std::array<uint8_t, " << N << "> const& x" << std::endl;
        if (column_length != N)
        {
            // Throw that column does not match describe table size
        }
    }
    
    void Deserialize(uint8_t const x[])
    {
        std::cout << "uint8_t const x[]" << std::endl;
    }
    
    void Deserialize(int const& x)
    {
        std::cout << "int const& x" << std::endl;
    }
    
    void Deserialize(std::string const& x)
    {
        std::cout << "std::string const& x" << std::endl;
    }
    
    void Deserialize(uint8_t const& x)
    {
        std::cout << "uint8_t const& x" << std::endl;
    }
    
    template<typename T>
    void operator()(const T& table_column)
    {
        if (column_pos++ == column_id)
        {
            this->Deserialize(table_column);
        }
    }
};

// Deserializes based on column filter and current column layout as defined within describe table
template<typename T>
void Deserialize(T& table, column_info_t const& column_info, ColumnFilter const& column_filter, payload_iter_t& current, payload_iter_t& end)
{
    if (column_filter == ColumnFilter::ALL_COLUMNS)
    {
        DeserializeColumn deserialize_handler;
        deserialize_handler.current_pos = current;
        deserialize_handler.end_pos = end;
        
        for (column_info_entry_t const& column_info_entry : column_info)
        {
            deserialize_handler.column_pos = 0;
            deserialize_handler.column_id = std::get<0>(column_info_entry);
            deserialize_handler.column_length = std::get<1>(column_info_entry);
            
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
            97,121,121,121,121,121,0,                   // Label
            98,97,121,98,97,97,121,121,                 // Location
    };
    
    DeviceModel device_model;
    
    // Example settings provided by describe table response
    device_model.device_table.table_info = DescribeTable{
            32,         // row count
            {0, 0},     // initial commit counters, should get updated after deserialization
            {
                column_info_entry_t(0,2,0),     // Device address id + length + type
                column_info_entry_t(1,16,0),    // Scenes id + length + type
                column_info_entry_t(2,32,0),    // Label id + length + type
                column_info_entry_t(3,8,0),     // Location id + length + type
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
}
