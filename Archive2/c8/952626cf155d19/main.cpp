#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <boost/property_tree/json_parser.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/foreach.hpp>

using namespace std;
using namespace boost::property_tree;

struct info_t
{
    string id;
    bool flag;
};

using obj_type = info_t;
template<class T> using list_type = vector<T>;

ostream& operator<<(ostream& os, info_t& info)
{
    os.setf(ios_base::boolalpha);
    os << "info_t{id:'" << info.id << "',flag:" << info.flag << "}";
    os.unsetf(ios_base::boolalpha);
    return os;
}

ostream& operator<<(ostream& os, const info_t& info)
{
    os.setf(ios_base::boolalpha);
    os << "info_t{id:'" << info.id << "',flag:" << info.flag << "}";
    os.unsetf(ios_base::boolalpha);
    return os;
}

template<typename T>
ostream& operator<<(ostream& os, const vector<T>& vec)
{
    os << "{";
    for (auto& el : vec)
    {
        os << el << ",";
    }
    os << "}";
    return os;
}

template<typename K, typename V>
ostream& operator<<(ostream& os, const map<K, V>& map)
{
    os << "{";
    for (auto& el : map)
    {
        os << "(" << el.first << "," << el.second << ")";
    }
    os << "}";
    return os;
}

bool from_json(string const & jsonStr, list_type<obj_type> & objList)
{
    istringstream inBuffer(jsonStr);
    ptree jsonObj;
    read_json(inBuffer, jsonObj);
    BOOST_FOREACH(ptree::value_type &item, jsonObj.get_child("objects"))
    {
        obj_type info;
        info.id = item.second.get_value<string>("id");
        info.flag = item.second.get_value<bool>("flag");
        objList.push_back(info);
    }
    return true;
}

bool to_json(list_type<obj_type> const & objList, string & out_jsonStr)
{
    ptree objects;
    for (auto it = objList.begin(); it != objList.end(); ++it)
    {
        ptree singleObj;
        singleObj.put("id", it->id);
        singleObj.put("flag", it->flag);
        objects.push_back(make_pair("", singleObj));
    }
    ptree jsonObj;
    jsonObj.add_child("objects", objects);
    ostringstream outBuffer;
    write_json(outBuffer, jsonObj);
    out_jsonStr = outBuffer.str();
    return true;
}

int main()
{
    vector<info_t> info_list = { { "a", false }, { "b", false }, { "c", true } };
    string as_json;
    to_json(info_list, as_json);
    cout << "serialised:\n";
    cout << as_json << "\n\n";
    
    vector<info_t> parsed_list;
    from_json(as_json, parsed_list);
    cout << "parsed:\n";
    cout << parsed_list << "\n\n";
    
    cout << "It works" << endl;   
}
