// ----- STL
#include <iostream>
#include <string>
#include <vector>
#include <map>

// ------ boost
#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/format.hpp>
#include <boost/foreach.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>

//formatter_base.hpp
//------------------------------------------------------------------------------
class formatter_base
{
protected:
    std::map<std::string, std::string> datas;
    
public:
    virtual ~formatter_base() {}
    void setvalue(std::string key, std::string value)
    {
        datas[key] = value;
    }

    std::string getvalue(std::string key)
    {
        return datas[key];
    }

    bool containsKey(std::string key)
    {
        return (datas.find(key) != datas.end());
    }

    virtual void deserialize(char *data, const std::size_t size) = 0;
    virtual std::string serialize(std::vector<std::string> keys) = 0;
};

//json_formatter.hpp
class json_formatter : public formatter_base
{
public:
    virtual void deserialize(char *data, const std::size_t size);
    virtual std::string serialize(std::vector<std::string> keys);
};


//datapacket.hpp
//------------------------------------------------------------------------------
class server;
extern server *tcp_server;

class datapacket
{
    static const char id[4];

public:
    enum DataFormat { BINARY = 0, JSON, XML };

    std::string ip;
    bool useHeader;

    datapacket() : useHeader(false), packet_data(NULL) {}
    datapacket(DataFormat format);
    std::vector<char> process(char *data, std::size_t size, std::string ip);

    std::string getvalue(std::string key)
    {
        return packet_data->getvalue(key);
    }

    void setvalue(std::string key, std::string value)
    {
        packet_data->setvalue(key, value);
    }

    bool containsKey(std::string key)
    {
        return packet_data->containsKey(key);
    }

    std::vector<char> serialize();
    std::string       toString();

private:
    bool deserialize(char *data, std::size_t size);
    std::string serialize_data(std::vector<std::string> keys);

    formatter_base *packet_data;
};

//datapacket.cpp
//------------------------------------------------------------------------------
#include <boost/iostreams/stream.hpp>
#include <boost/foreach.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <string.h>

datapacket::datapacket(DataFormat format)
: useHeader(false)
{
    if(format == JSON)
    {
        packet_data = new json_formatter();
    }
    else
    {
        packet_data = NULL;
    }
}


std::vector<char> datapacket::process(
                                      char *data, std::size_t size, std::string ip)
{
    std::cout << "datapacket::process" << std::endl;

    this->ip = ip;
    std::vector<char> ret;

    if (!deserialize(data, size))
        return ret;

    std::vector<std::string> keys;
    std::string result;

    /*extern void process(datapacket& gamedata);
     process(*this);*/

    ret.push_back('a');
    ret.push_back('c');
    ret.push_back('k');

    return ret;
}

bool datapacket::deserialize(char *data, std::size_t size)
{
    packet_data = new json_formatter();
    packet_data->deserialize(data, size);
    return true;
}

std::string datapacket::serialize_data(std::vector<std::string> keys)
{
    return packet_data->serialize(keys);
}

std::vector<char> datapacket::serialize()
{
    std::vector<std::string> keys;
    std::string str = serialize_data(keys);
    std::vector<char> ret;
    ret.assign(str.begin(), str.end());

    return ret;
}

std::string datapacket::toString()
{
    std::vector<std::string> keys;
    std::string str = serialize_data(keys);

    return str;
}


//json_formatter.cpp
//------------------------------------------------------------------------------
using namespace boost::property_tree;

void json_formatter::deserialize(char *data, const std::size_t size)
{
    std::stringstream ss;
    ss.write(data, size);

    //  std::cout << "ss: " << ss.str() << std::endl;

    ptree pt;
    read_json(ss, pt);

    BOOST_FOREACH(ptree::value_type &v, pt)
    {
        //log all received data
        //std::cout << v.first.data() << ": " << v.second.data() << std::endl;

        datas[v.first.data()] = v.second.data();
    }
}

///-workaround 1.57 json
template <typename T>
struct my_id_translator
{
    typedef T internal_type;
    typedef T external_type;

    boost::optional<T> get_value(const T &v) { return  v.substr(1, v.size() - 2) ; }
    boost::optional<T> put_value(const T &v) { return '"' + v + '"'; }
};
///
std::string json_formatter::serialize(std::vector<std::string> keys)
{


    ptree pt;

    if(keys.empty())
    {
        typedef std::map<std::string, std::string> mapType;
        BOOST_FOREACH(const mapType::value_type& myPair, datas)
        {
            //workaround for wrong formatted string
            if((BOOST_VERSION == 105700) && (BOOST_OS_LINUX))
            {
                //1.57
                pt.put(myPair.first, myPair.second, my_id_translator<std::string>());
            }
            else
            {
                //1.54
                pt.put(myPair.first, myPair.second);
            }
            std::cout << myPair.first << ": " << myPair.second << std::endl;
        }
    }
    else
    {
        BOOST_FOREACH(std::string key, keys)
        {
            //workaround for wrong formatted string
            if(BOOST_VERSION == 105700)
            {
#if BOOST_OS_LINUX
                pt.put(key, "\"" + datas[key] + "\"", my_id_translator<std::string>());
#else
                pt.put(key, datas[key], my_id_translator<std::string>());
#endif
            }
            else
            {
                pt.put(key, datas[key]);
            }
            //      std::cout << key << ": " << datas[key] << std::endl;
        }
    }

    std::stringstream ss;
    write_json(ss, pt);
    std::string str = ss.str();

    // WORKAROUND
    // Replace all escaped backslashes
    // This was because some clients couldn't interpret "command\\/read"
    std::string oldStr = "\\/";
    std::string newStr = "/";

    std::size_t pos = 0;
    while((pos = str.find(oldStr)) != std::string::npos){
        str = str.replace(pos, oldStr.length(), newStr);
        pos += newStr.length();
    }
    // /WORKAROUND

    //std::cout << "Serialize message:" << std::endl;
    //std::cout << str << std::endl;
    return str;
}


//main.cpp
//------------------------------------------------------------------------------
class dataClass
{
public:
    dataClass() {}
    std::string name;
};

class innerDataClass
{
public:
    innerDataClass() {}
    std::string name;
    int         score;
    std::string baseClassName;
};

using boost::asio::ip::tcp;


namespace stdpatch
{
    template <typename T> std::string to_string(const T& n)
    {
        std::ostringstream stm;
        stm << n;
        return stm.str();
    }
}

std::map<std::string, dataClass>        listDC;
std::map<std::string, innerDataClass>   listIDC;

void Init()
{
    //Some initial values
    dataClass d1; d1.name = "dataClass1"; listDC["d1"] = d1;
    dataClass d2; d2.name = "dataClass2"; listDC["d2"] = d2;

    innerDataClass i1; i1.name = "innerClass1"; i1.baseClassName = "dataClass1";
    i1.score = 5; listIDC["i1"] = i1;
    innerDataClass i2; i2.name = "innerClass2"; i2.baseClassName = "dataClass1";
    i1.score = 21; listIDC["i2"] = i2;
    innerDataClass i3; i3.name = "innerClass3"; i1.baseClassName = "dataClass2";
    i1.score = 1; listIDC["i3"] = i3;
}

//returns JSON
datapacket GetJSON()
{
    std::pair<std::string, dataClass>       baseClassPair;
    std::pair<std::string, innerDataClass>  innerClassPair;

    datapacket baseClasses (datapacket::JSON);
    baseClasses.setvalue("comment", "this holds all the base classes");
    BOOST_FOREACH(baseClassPair, listDC)
    {
        datapacket baseClassData (datapacket::JSON);
        baseClassData.setvalue("dataName", baseClassPair.first);
        BOOST_FOREACH(innerClassPair, listIDC)
        {
            if (innerClassPair.second.baseClassName == baseClassPair.second.name)
            {
                datapacket innerClassData (datapacket::JSON);
                innerClassData.setvalue(
                                        "name", innerClassPair.second.name);
                innerClassData.setvalue(
                                        "gameID", stdpatch::to_string(innerClassPair.second.score));

                baseClassData.setvalue(
                                       "inner " + innerClassPair.first, innerClassData.toString());
            }
        }
        baseClasses.setvalue("base " + baseClassPair.first, baseClassData.toString());
    }

    datapacket packet (datapacket::JSON);
    packet.setvalue("comment", "this is the base-packet");
    packet.setvalue("baseClasses", baseClasses.toString());
    return packet;
}


int main()
{
    Init();
    datapacket packet (datapacket::JSON);
    packet = GetJSON();

    std::cout << std::endl << std::endl
              << "------------- RESULT --------------"
              << std::endl << std::endl;

    std::cout << packet.toString() << std::endl;

    return 0;
}
