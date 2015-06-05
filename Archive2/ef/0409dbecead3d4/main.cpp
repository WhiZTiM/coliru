#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <iostream>

using boost::property_tree::ptree;

int main()
{
    ptree pt;

    pt.add("TokenNo", "Deb123456");
    pt.add("CPUID", "Deb123456");
    pt.add("CommandID", "05");
    pt.add("IsEncrypted", "0");
    pt.add("CommandString..ADD", "97");
    pt.add("CommandString..ESTBCODE", "99999999");
    pt.add("CommandString..EID", "XY");
    pt.add("CommandString..CID", "0154400000");
    pt.add("CommandString..DATE", "14042015");
    pt.add("CommandString..TIME", "1835");
    pt.add("CommandString..IOMODE", "I");
    pt.add("CommandString..REASONCODE", "55");
    pt.add("CommandString..LAT", "87");
    pt.add("CommandString..LONG", "90");
    pt.add("CommandString..ADD", "87");
    pt.add("CommandString..ESTBCODE", "99999998");
    pt.add("CommandString..EID", "XX");
    pt.add("CommandString..CID", "0154300000");
    pt.add("CommandString..DATE", "15052015");
    pt.add("CommandString..TIME", "1946");
    pt.add("CommandString..IOMODE", "I");
    pt.add("CommandString..REASONCODE", "56");
    pt.add("CommandString..LAT", "88");
    pt.add("CommandString..LONG", "91");
    pt.add("CommandString..ADD", "88");
    pt.add("CommandString..ESTBCODE", "99999998");
    pt.add("CommandString..EID", "XX");
    pt.add("CommandString..CID", "0154300000");
    pt.add("CommandString..DATE", "15052015");
    pt.add("CommandString..TIME", "1946");
    pt.add("CommandString..IOMODE", "I");
    pt.add("CommandString..REASONCODE", "56");
    pt.add("CommandString..LAT", "88");
    pt.add("CommandString..LONG", "91");

    write_json(std::cout, pt);
}
