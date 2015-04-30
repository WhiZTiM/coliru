#include <iostream>
#include <string>
#include <vector>
#include <tuple>
#include <map>

#include <functional>
#include <typeinfo>

#include <boost/fusion/include/adapt_struct.hpp>
#include <boost/fusion/include/algorithm.hpp>
#include <boost/fusion/include/begin.hpp>
#include <boost/fusion/include/end.hpp>
#include <boost/fusion/include/deref.hpp>
#include <boost/fusion/include/next.hpp>

struct DeviceTable
{
    int device_address;
    uint8_t scenes[16];
    std::string label;
    std::string location;
};

BOOST_FUSION_ADAPT_STRUCT(DeviceTable, (int, device_address)(uint8_t, scenes[16])(std::string, label)(std::string, location))

struct WLANTable
{
    uint8_t mac_address[6];
    std::string ssid;
    std::string password;
};

BOOST_FUSION_ADAPT_STRUCT(WLANTable, (uint8_t, mac_address[6])(std::string, ssid)(std::string, password))

class DeviceModel
{
public:
    std::map<unsigned int, DeviceTable> device_table;
    std::map<unsigned int, WLANTable> wlan_table;
    
    
};

struct PrintVars
{
    template <typename T>
    void operator()(T const & x) const
    {
        std::cout << '<' << typeid(x).name() <<  ' ' << x << '>';
    }
};

template <typename T>
void test_print(T const & x)
{
    std::cout << '<' << typeid(x).name() <<  ' ' << x << '>';
}

template <typename T1, typename T2>
void IterateVars(T1 const& current, T2 const& end)
{
    if (current != end)
    {
        //test_print(boost::fusion::deref(current));
        
        auto& a = boost::fusion::next(current);
        
        IterateVars(a, end);
    }
}


template<typename T>
void Deserialize(std::vector<uint8_t> payload, T& output)
{
    auto& it = boost::fusion::begin(output);
    auto& end = boost::fusion::end(output); 
    
    
    auto& a = boost::fusion::next(it);
    
    if (a != end)
    {
        std::cout << "not end\n";
    }
    
    auto& b = boost::fusion::next(a);
    
    if (b != end)
    {
        std::cout << "not end\n";
    }
    
    /*if (it != boost::fusion::end(output))
    {
        std::cout << "Not end\n";
    }*/
    
    IterateVars(it, end);
    
    //while (
    
    
    
    
    boost::fusion::for_each(output, PrintVars());
    
    
    //PrintVars());
}



template<typename... Args>
void Deserialize(std::vector<uint8_t> payload, std::tuple<Args...>& output)
{
    for (unsigned int i = 0; i < sizeof...(Args); i++)
    {
        std::cout << i << std::endl;
    }
}




int main()
{
    std::vector<uint8_t> payload = {1,2,3,4};
    std::tuple<int,uint8_t,std::string> res; 
    
    DeviceModel device_model;
    device_model.device_table[0] = DeviceTable{1, {1,2,3,4,5,6}, "abc", "def"};
    
    
    Deserialize(payload, device_model.device_table[0]);
    
    
    
    Deserialize(payload, res);
}
