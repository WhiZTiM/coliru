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
    // Zero initialise
    ClientHeader() :
            command(static_cast<DatabaseCommand>(0)),
            table(Table{static_cast<TableFilter>(0), Version{0,0}}),
            filters(Filters{static_cast<ColumnFilter>(0), static_cast<RowFilter>(0)})
    {
        
    }
    
    ClientHeader(DatabaseCommand _command, Table _table, Filters _filters) :
            command(_command),
            table(_table),
            filters(_filters)
    {
        
    }
    
    ClientHeader(DatabaseCommand _command, Table _table, Filters _filters, bool _CMT) :
            command(_command),
            table(_table),
            filters(_filters),
            CMT(_CMT)
    {
        
    }
    
    ClientHeader(
            DatabaseCommand _command, 
            Table _table, 
            Filters _filters, 
            std::vector<uint8_t> _data) :
            command(_command),
            table(_table),
            filters(_filters),
            DAT(true),
            data(_data)
    {
        
    }
    
    ClientHeader(
            DatabaseCommand _command, 
            Table _table, 
            Filters _filters, 
            bool _CMT, 
            std::vector<uint8_t> _data) :
            command(_command),
            table(_table),
            filters(_filters),
            CMT(_CMT),
            DAT(true),
            data(_data)
    {
        
    }
    
    DatabaseCommand command;
    Table table;
    Filters filters;
    bool CMT = false;
    bool DAT = false;
    std::vector<uint8_t> data;
};

/*******************************************************************************/

// There's going to be two main namespaces - server and client. Server will be responsible
// for serializing/deserializing server database headers. Client will be responsible for client
// headers. The serialization/deserialization will be from structs which represent both client

namespace client
{
    static const uint32_t client_header_size = 8;
    
    // Client serialize
    
    template<typename OutputIter>
    void SerializeCommand(const DatabaseCommand& command, OutputIter& output_iter)
    {
        *output_iter++ = static_cast<uint8_t>(command);
    }
    
    template<typename OutputIter>
    void SerializeTable(const Table& table, OutputIter& output_iter)
    {
        *output_iter++ = static_cast<uint8_t>(table.table_filter);
        *output_iter++ = table.version.Major;
        *output_iter++ = table.version.Minor;
    }
    
    uint8_t GetFlagsByte(const bool& DAT, const bool& CMT)
    {
        uint8_t flags = 0;
        
        if (DAT)
        {
            flags |= 0x80;
        }
        
        if (CMT)
        {
            flags |= 0x20;
        }
        
        return flags;
    }
    
    template<typename OutputIter>
    void SerializeFlagsAndFilters(
            const bool& DAT,
            const bool& CMT,
            const Filters& filters,
            OutputIter& output_iter )
    {
        uint8_t flags = GetFlagsByte(DAT, CMT);
        
        // Set column filter
        uint16_t column_filter = static_cast<uint16_t>(filters.column_filter);
        
        flags |= (uint8_t)(column_filter >> 8);
        *output_iter++ = flags;
        *output_iter++ = (uint8_t)column_filter;
        
        // Set row filter
        uint16_t row_filter = static_cast<uint16_t>(filters.row_filter);
        
        *output_iter++ = (uint8_t)(row_filter >> 8);
        *output_iter++ = (uint8_t)row_filter;
    }
    
    template<typename OutputIter>
    void SerializeData(const std::vector<uint8_t>& data, OutputIter& output_iter)
    {
        for (unsigned int i = 0; i < data.size(); ++i, ++output_iter)
        {
            *output_iter = data[i];
        }
    }
    
    // Data, cmt by default
    template<typename OutputIter>
    void Serialize(
            const DatabaseCommand& command, 
            const Table& table, 
            const Filters& filters, 
            const std::vector<uint8_t>& data, 
            OutputIter& output_iter )
    {
        SerializeCommand(command, output_iter);
        SerializeTable(table, output_iter);
        SerializeFlagsAndFilters(true, true, filters, output_iter);
        SerializeData(data, output_iter);
    }
    
    // No data flag, cmt by default
    template<typename OutputIter>
    void Serialize(
            const DatabaseCommand& command,
            const Table& table, 
            const Filters& filters, 
            OutputIter& output_iter )
    {
        SerializeCommand(command, output_iter);
        SerializeTable(table, output_iter);
        SerializeFlagsAndFilters(false, true, filters, output_iter);
    }
    
    template<typename OutputIter>
    void Serialize(ClientHeader const& header_in, OutputIter& output_iter)
    {
        SerializeCommand(header_in.command, output_iter);
        SerializeTable(header_in.table, output_iter);
        SerializeFlagsAndFilters(header_in.DAT, header_in.CMT, header_in.filters, output_iter);
        
        // Only serialize data if the DAT flag has been set
        if (header_in.DAT)
        {
            SerializeData(header_in.data, output_iter);
        }
    }
    
    // Full client header where all flags are set
    void Serialize(ClientHeader const& header_in, std::vector<uint8_t>& payload_out)
    {
        payload_out.reserve(payload_out.size() + client_header_size + header_in.data.size());
        auto back_inserter = std::back_inserter(payload_out);
        Serialize(header_in, back_inserter);
    }
    
/****************************************************************************************************/

// Client deserialize
    
    template<typename InputIter>
    void DeserializeCommand(ClientHeader& header_out, InputIter& current)
    {
        header_out.command = static_cast<DatabaseCommand>(*current++);
    }
    
    template<typename InputIter>
    void DeserializeTable(ClientHeader& header_out, InputIter& current)
    {
        header_out.table.table_filter = static_cast<TableFilter>(*current++);
        
        uint8_t table_major = *current++;
        uint8_t table_minor = *current++;
        
        header_out.table.version = Version{table_major, table_minor};
    }
    
    void DeserializeFlags(ClientHeader& header_out, const uint8_t& flags)
    {
        header_out.DAT = (flags & 0x80) > 0;
        header_out.CMT = (flags & 0x20) > 0;
    }
    
    template<typename InputIter>
    void DeserializeFlagsAndFilters(ClientHeader& header_out, InputIter& current)
    {
        // Flags
        uint8_t flags = *current++;
        DeserializeFlags(header_out, flags);
        
        // Column filter
        uint16_t column_filter = (flags & 0x1F);
        column_filter = (column_filter << 8) | *current++;
        
        // Row filter
        uint16_t row_filter = *current++;
        row_filter = (row_filter << 8) | *current++;
        
        header_out.filters = Filters{static_cast<ColumnFilter>(column_filter), static_cast<RowFilter>(row_filter)};
    }
    
    template<typename InputIter>
    void DeserializeData(ClientHeader& header_out, InputIter& current, const InputIter& end)
    {
        // Assumes all other fileds of header_out have been set before calling this method
        if (!header_out.DAT && !header_out.CMT && current != end)
        {
            // Flags are set to false and there is data in payload
            throw std::exception();
        }
        
        header_out.data.reserve(end - current);
        
        for (; current != end; ++current)
        {
            header_out.data.push_back(*current);
        }
    }
    
    template<typename InputIter>
    void Deserialize(ClientHeader& header_out, InputIter& begin, const InputIter& end)
    {
        // Check header size
        if ((end - begin) < client_header_size)
        {
            throw std::exception();
        }
        
        DeserializeCommand(header_out, begin);
        DeserializeTable(header_out, begin);
        DeserializeFlagsAndFilters(header_out, begin);
        DeserializeData(header_out, begin, end);
    }
    
    
    void Deserialize(ClientHeader& header_out, const std::vector<uint8_t>& payload_in)
    {
        auto begin = std::begin(payload_in);
        auto end = std::end(payload_in);
        
        Deserialize(header_out, begin, end);
    }
}   // client

/****************************************************************************************************/

// Examples

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

void ClientSerializeExample()
{
    std::vector<uint8_t> payload;
    
    ClientHeader header_to_serialize(
            DatabaseCommand::UPDATE,
            Table{TableFilter::ALL_TABLES, Version{1,2}},
            Filters{ColumnFilter::ALL_COLUMNS, RowFilter::ALL_ROWS},
            false,
            std::vector<uint8_t>{0x00,0x01,0x02,0x03,0x04,0x05}
    );
    
    client::Serialize(header_to_serialize, payload);
    
    std::vector<uint8_t> expected_data = 
            {0x01, 0xFF, 0x01, 0x02, 0x9F, 0xFF, 0xFF, 0xFF, 0x00, 0x01, 0x02, 0x03, 0x04, 0x05};
            
    assert(payload == expected_data);
}

int main()
{
    ClientDeserializeExample();
    ClientSerializeExample();
}
