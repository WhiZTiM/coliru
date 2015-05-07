#include <cstdint>
#include <iterator>
#include <vector>

// Example requirements
#include <cassert>
#include <iostream>
#include <algorithm> // for copy

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

struct ServerHeader
{
    // Zero initialise
    ServerHeader() : table_version(Version{0,0})
    { }
    
    // Error
    ServerHeader(Version _table_version, bool _ERR, uint8_t _flag_data)
            : table_version(_table_version),
              ERR(_ERR),
              flag_data(_flag_data)
    { }
    
    // Data (cmt default)
    ServerHeader(Version _table_version, const std::vector<uint8_t>& _data)
            : table_version(_table_version),
              CMT(true),
              DAT(true),
              data(_data)
    { }
    
    // Data (cmt specified)
    ServerHeader(Version _table_version, bool _CMT, const std::vector<uint8_t>& _data)
            : table_version(_table_version),
              CMT(_CMT),
              DAT(true),
              data(_data)
    { }
    
    Version table_version;
    bool CMT = false;
    bool DAT = false;
    bool ERR = false;
    bool RST = false;
    uint8_t flag_data = 0;
    std::vector<uint8_t> data;
};

/****************************************************************************************************/

// There's going to be two main namespaces - server and client. Server will be responsible
// for serializing/deserializing server database headers. Client will be responsible for client
// headers. The serialization/deserialization will be from structs which represent both client
// and server header types.

namespace server
{
    static const uint32_t server_header_size = 4;
    
    // Server serialize
    
    template<typename OutputIter>
    void SerializeTableVersion(const Version& table_version, OutputIter& output_iter)
    {
        *output_iter++ = table_version.Major;
        *output_iter++ = table_version.Minor;
    }
    
    template<typename OutputIter>
    void SerializeFlags(const ServerHeader& header_in, OutputIter& output_iter)
    {
        uint8_t flags = 0;
        
        if (header_in.DAT)
        {
            flags |= 0x80;
        }
        
        if (header_in.CMT)
        {
            flags |= 0x40;
        }
        
        if (header_in.ERR)
        {
            flags |= 0x10;
        }
        
        if (header_in.RST)
        {
            flags |= 0x08;
        }
        
        *output_iter++ = flags;
    }
    
    template<typename OutputIter>
    void SerializeFlagData(const uint8_t& flag_data, OutputIter& output_iter)
    {
        *output_iter++ = flag_data;
    }
    
    template<typename OutputIter>
    void SerializeData(const std::vector<uint8_t>& data, OutputIter& output_iter)
    {
        for (unsigned int i = 0; i < data.size(); ++i, ++output_iter)
        {
            *output_iter = data[i];
        }
    }
    
    template<typename OutputIter>
    void Serialize(const ServerHeader& header_in, OutputIter& output_iter)
    {
        SerializeTableVersion(header_in.table_version, output_iter);
        SerializeFlags(header_in, output_iter);
        SerializeFlagData(header_in.flag_data, output_iter);
        
        if (header_in.DAT || header_in.CMT)
        {
            SerializeData(header_in.data, output_iter);
        }
    }
    
    void Serialize(const ServerHeader& header_in, std::vector<uint8_t>& payload_out)
    {
        payload_out.reserve(payload_out.size() + server_header_size + header_in.data.size());
        auto back_inserter = std::back_inserter(payload_out);
        Serialize(header_in, back_inserter);
    }
    
/****************************************************************************************************/

    // Server deserialize
    template<typename InputIter>
    void DeserializeTableVersion(ServerHeader& header_out, InputIter& current)
    {
        uint8_t major = *current++;
        uint8_t minor = *current++;
        
        header_out.table_version = Version{major, minor};
    }
    
    template<typename InputIter>
    void DeserializeFlags(ServerHeader& header_out, InputIter& current)
    {
        uint8_t flags = *current++;
        
        header_out.DAT = (flags & 0x80) > 0;
        header_out.CMT= (flags & 0x40) > 0;
        header_out.ERR = (flags & 0x10) > 0;
        header_out.RST = (flags & 0x08) > 0;
    }
    
    template<typename InputIter>
    void DeserializeFlagData(ServerHeader& header_out, InputIter& current)
    {
        header_out.flag_data = *current++;
    }
    
    template<typename InputIter>
    void DeserializeData(ServerHeader& header_out, InputIter& current, const InputIter& end)
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
    void Deserialize(ServerHeader& header_out, InputIter& begin, const InputIter& end)
    {
        // Check header size
        if ((end - begin) < server_header_size)
        {
            throw std::exception();
        }
        
        DeserializeTableVersion(header_out, begin);
        DeserializeFlags(header_out, begin);
        DeserializeFlagData(header_out, begin);
        DeserializeData(header_out, begin, end);
    }
    
    void Deserialize(ServerHeader& header_out, std::vector<uint8_t> const& payload_in)
    {
        auto begin = std::begin(payload_in);
        auto end = std::end(payload_in);
        
        Deserialize(header_out, begin, end);
    }
}   // server

/****************************************************************************************************/

// Examples

void ServerDeserializeExample()
{
    std::vector<uint8_t> payload = {
            0x05, 0xF1,     // Table version
            0xC8,           // Flags
            0xFC,           // Flag data
            0x01, 0x02, 0x03, 0x04, 0x05,   // Test data
    };
    
    ServerHeader deserialized_header;
    
    server::Deserialize(deserialized_header, payload);
    
    std::vector<uint8_t> expected_data = {0x01, 0x02, 0x03, 0x04, 0x05};
    
    assert(deserialized_header.table_version.Major == 0x05);
    assert(deserialized_header.table_version.Minor == 0xF1);
    assert(deserialized_header.DAT == true);
    assert(deserialized_header.CMT == true);
    assert(deserialized_header.ERR == false);
    assert(deserialized_header.RST == true);
    assert(deserialized_header.flag_data == 0xFC);
    assert(deserialized_header.data == expected_data);
}

void ServerSerializeExample()
{
    std::vector<uint8_t> payload;
    
    ServerHeader header_to_serialize(
            Version{0x05, 0xF1},
            std::vector<uint8_t>{0x00,0x01,0x02,0x03,0x04,0x05}
    );
    
    server::Serialize(header_to_serialize, payload);
    
    std::vector<uint8_t> expected_data = {0x05, 0xF1, 0xC0, 0x00, 0x00, 0x01, 0x02, 0x03, 0x04, 0x05};
            
    assert(payload == expected_data);
}

int main()
{
    ServerDeserializeExample();
    ServerSerializeExample();
}
