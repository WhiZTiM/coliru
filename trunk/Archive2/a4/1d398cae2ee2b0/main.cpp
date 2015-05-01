#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <functional>

#include <boost/fusion/include/at_c.hpp>
#include <boost/fusion/include/adapt_struct.hpp>
#include <boost/fusion/include/algorithm.hpp>

struct DeviceTable
{
    int device_address;
    uint8_t scenes[16];
    std::string label;
    std::string location;
};

struct DeviceTableIndex
{
    int device_address = 1;
    int scenes = 2;
    int label = 3;
    int location = 4;
};

static const DeviceTableIndex device_table_index;

BOOST_FUSION_ADAPT_STRUCT(
        DeviceTable, 
        (int, device_address)
        (uint8_t, scenes[16])
        (std::string, label)
        (std::string, location)
)
BOOST_FUSION_ADAPT_STRUCT(
        DeviceTableIndex, 
        (int, device_address)
        (int, scenes)
        (int, label)
        (int, location)
)

struct WLANTable
{
    uint8_t mac_address[6];
    std::string ssid;
    std::string password;
};

BOOST_FUSION_ADAPT_STRUCT(WLANTable, (uint8_t, mac_address[6])(std::string, ssid)(std::string, password))

boost::fusion::zip_view<boost::fusion::vector2<const DeviceTableIndex&, const DeviceTable&>> 
GetZip(const DeviceTable& device_table)
{
    return boost::fusion::zip(device_table_index, device_table);
}

class DeviceModel
{
public:
    std::map<unsigned int, DeviceTable> device_table;
    std::map<unsigned int, WLANTable> wlan_table;
    
    
};

struct PrintPair
{
    template <typename T>
    void operator()(T const & x)
    {
        std::cout << "First: " << boost::fusion::at_c<0>(x) << std::endl;
        std::cout << "Second: " << boost::fusion::at_c<1>(x) << std::endl;
    }
};

int main()
{
    std::vector<uint8_t> payload = {1,2,3,4,5};
    
    DeviceModel device_model;
    device_model.device_table[0] = DeviceTable{1, {1,2,3,4,5,6}, "abc", "def"};
    
    
    auto zippity = GetZip(device_model.device_table[0]);
    
    PrintPair p;
    boost::fusion::for_each(zippity, std::ref(p));
}