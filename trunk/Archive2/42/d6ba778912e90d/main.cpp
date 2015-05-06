#include <cstdint>
#include <iterator>
#include <vector>

// Example requirements
#include <cassert>
#include <iostream>

#include <boost/asio/io_service.hpp>
#include <boost/asio/steady_timer.hpp>
#include <boost/system/error_code.hpp>
#include <chrono>

/*******************************************************************************/

// From "mncp/common/types.hpp"

struct Version
{
	/** @brief The major version. */
	uint8_t Major;
	/** @brief The minor version. */
	uint8_t Minor;
};

/*******************************************************************************/

typedef uint16_t column_id_t;
typedef uint16_t row_id_t;
typedef uint8_t  table_id_t;
typedef uint8_t  command_t;

enum class DatabaseCommand : command_t
{
    SELECT          = 0x00,
    UPDATE          = 0x01,
    INSERT          = 0x02,
    DELETE          = 0x03,
    SHOW_TABLES     = 0x04,
    DESCRIBE_TABLE  = 0x05,
    TABLE_STATUS    = 0x06,
};

enum class ColumnFilter : column_id_t
{
    ALL_COLUMNS = 0x1FFF,
};

enum class RowFilter : row_id_t
{
    ALL_ROWS = 0xFFFF,
};

enum class TableFilter : table_id_t
{
    ALL_TABLES = 0xFF,
};

struct Table
{
    TableFilter table_filter;
    Version version;
};

struct Filters
{
    ColumnFilter column_filter;
    RowFilter row_filter;
};

struct ClientHeader
{
    DatabaseCommand command;
    Table table;
    bool CMT = false;
    bool DAT = false;
    Filters filters;
    std::vector<uint8_t> data;
};

struct ServerHeader
{
    Version table_version;
    bool CMT = false;
    bool DAT = false;
    bool ERR = false;
    bool RST = false;
    uint8_t flag_data;
    std::vector<uint8_t> data;
};

/*******************************************************************************/

// There's going to be two main namespaces - server and client. Server will be responsible
// for serializing/deserializing server database headers. Client will be responsible for client
// headers. The serialization/deserialization will be from structs which represent both client
// and server header types.

namespace server
{
    static const uint32_t server_header_size = 4;
    
    void Serialize(ServerHeader const& header_in, std::vector<uint8_t>& payload_out)
    {
        
    }
    
    void Deserialize(ServerHeader& header_out, std::vector<uint8_t> const& payload_in)
    {
        // Check header size
        if (payload_in.size() < server_header_size)
        {
            throw std::exception();
        }
        
        
        
        
    }
}   // server

namespace client
{
    static const uint32_t client_header_size = 8;
    
    // Considering having a few overloads for serialize which simplify creating a header
    // One will accept booleans defining if there is data/cmt flag, + table, column and row filters
    // And there is this version which takes the actual header and serializes as specified 
    void Serialize(ClientHeader const& header_in, std::vector<uint8_t>& payload_out)
    {
        payload_out.reserve(payload_out.size() + client_header_size + header_in.data.size());
        
        auto back_inserter = std::back_inserter(payload_out);
        
        // Command
        *back_inserter++ = static_cast<uint8_t>(header_in.command);
        
        // Table
        *back_inserter++ = static_cast<uint8_t>(header_in.table.table_filter);
        *back_inserter++ = header_in.table.version.Major;
        *back_inserter++ = header_in.table.version.Minor;
        
        // Flags
        uint8_t flags = 0;
        
        if (header_in.DAT)
        {
            flags |= 0x80;
        }
        
        if (header_in.CMT)
        {
            flags |= 0x20;
        }
        
        // Column filter
        uint16_t column_filter = static_cast<uint16_t>(header_in.filters.column_filter);
        
        flags |= (uint8_t)(column_filter >> 8);
        *back_inserter++ = flags;
        *back_inserter++ = (uint8_t)column_filter;
        
        // Row filter
        uint16_t row_filter = static_cast<uint16_t>(header_in.filters.row_filter);
        
        *back_inserter++ = (uint8_t)(row_filter >> 8);
        *back_inserter++ = (uint8_t)row_filter;
        
        // Data
        for (unsigned int i = 0; i < header_in.data.size(); ++i, ++back_inserter)
        {
            *back_inserter = header_in.data[i];
        }
    }
    
    void Deserialize(ClientHeader& header_out, std::vector<uint8_t> const& payload_in)
    {
        // Check header size
        if (payload_in.size() < client_header_size)
        {
            throw std::exception();
        }
        
        std::vector<uint8_t>::const_iterator current = std::begin(payload_in);
        std::vector<uint8_t>::const_iterator const end = std::end(payload_in);
        
        // Command
        header_out.command = static_cast<DatabaseCommand>(*current++);
        
        // Table
        header_out.table.table_filter = static_cast<TableFilter>(*current++);
        
        uint8_t table_major = *current++;
        uint8_t table_minor = *current++;
        
        header_out.table.version = Version{table_major, table_minor};
        
        // Flags
        uint8_t flags = *current++;
        
        header_out.DAT = (flags & 0x80) > 0;
        header_out.CMT = (flags & 0x20) > 0;
        
        // Filters
        uint16_t column_filter = (flags & 0x1F);
        column_filter = (column_filter << 8) | *current++;
        
        uint16_t row_filter = *current++;
        row_filter = (row_filter << 8) | *current++;
        
        header_out.filters = Filters{static_cast<ColumnFilter>(column_filter), static_cast<RowFilter>(row_filter)};
        
        // Data
        header_out.data.reserve(end - current);
        
        for (; current != end; ++current)
        {
            header_out.data.push_back(*current);
        }
    }
}   // client


void ClientDeserializeExample()
{
    std::vector<uint8_t> payload = {
            0x00,           // Command (select)
            0x10,           // Table id
            0x05, 0x88,     // Table version
            0xBF, 0xFF,     // Flags + column filter (all columns)
            0x00, 0x07,     // Row filter
            0x00, 0x01, 0x02, 0x03, // Some test data
    };
    
    ClientHeader deserialized_header;
    
    client::Deserialize(deserialized_header, payload);
    
    std::vector<uint8_t> expected_data = {0x00, 0x01, 0x02, 0x03};
    
    assert(deserialized_header.command == DatabaseCommand::SELECT);
    assert(deserialized_header.table.table_filter == static_cast<TableFilter>(0x10));
    assert(deserialized_header.table.version.Major == 0x05);
    assert(deserialized_header.table.version.Minor == 0x88);
    assert(deserialized_header.DAT == true);
    assert(deserialized_header.CMT == true);
    assert(deserialized_header.filters.column_filter == ColumnFilter::ALL_COLUMNS);
    assert(deserialized_header.filters.row_filter == static_cast<RowFilter>(0x07));
    assert(deserialized_header.data == expected_data);
}

/*DatabaseCommand command;
    Table table;
    bool CMT = false;
    bool DAT = false;
    Filters filters;
    std::vector<uint8_t> data;*/

void ClientSerializeExample()
{
    std::vector<uint8_t> payload;
    
    /*ClientHeader header_to_serialize = ClientHeader{ 
            DatabaseCommand::UPDATE,
            Table{TableFilter::ALL_TABLES, Version{1,2}},
            true,
            true,
            Filters{ColumnFilter::ALL_COLUMNS, RowFilter::ALL_ROWS},
            std::vector<uint8_t>{0x00,0x01,0x02,0x03,0x04,0x05},
    };*/
    
    
}

int main()
{
    ClientDeserializeExample();
    ClientSerializeExample();
}

