#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <iostream>
#include <sstream>

using boost::property_tree::ptree;

int main()
{
    ptree pt;
    pt.add("TokenNo",       "Deb123456");
    pt.add("CPUID",         "Deb123456");
    pt.add("CommandID",     "05");
    pt.add("CommandStatus", "null");
    pt.add("IsEncrypted",   "0");

    ptree cs;
    cs.add("Add",           "97");
    cs.add("EstbCD",        "99999999");
    cs.add("EID",           "XY");
    cs.add("CID",           "0154400000");
    cs.add("DATE",          "14042015");
    cs.add("TIME",          "1835");
    cs.add("IOMODE",        "I");
    cs.add("REASONCODE",    "55");
    cs.add("LAT",           "87");

#if 1 // if you are a sane person
    pt.put_child("CommandString", cs);
#else
    // or, if you really wanted braindead non-JSON:
    std::ostringstream oss;
    write_json(oss, cs);

    pt.put("CommandString", oss.str());
#endif
    write_json(std::cout, pt);
}
