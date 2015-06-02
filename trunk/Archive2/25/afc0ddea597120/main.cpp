#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <iostream>

using Tree = boost::property_tree::ptree;

static inline std::string to_string(Tree const& tree) {
    std::ostringstream oss;
    boost::property_tree::write_json(oss, tree);
    return oss.str();
}

struct AttendanceT {
    std::string Addr;
    std::string EstablishmentCode;
    std::string EmployeeID;
    std::string CardID;
    std::string PunchDate;
    std::string PunchTime;
    std::string InOutMode;
    std::string ReasonCode;
    std::string Lat;
    std::string Long;

    Tree to_tree() const {
        Tree pt;
        pt.put("ADD",        Addr);
        pt.put("ESTBCODE",   EstablishmentCode);
        pt.put("EID",        EmployeeID);
        pt.put("CID",        CardID);
        pt.put("DATE",       PunchDate);
        pt.put("TIME",       PunchTime);
        pt.put("IOMODE",     InOutMode);
        pt.put("REASONCODE", ReasonCode);
        pt.put("LAT",        Lat);
        pt.put("LONG",       Long);

        return pt;
    }
};

struct POST3 {
    std::string TokenNo;
    std::string CPUID;
    std::string CommandID;
    std::string IsEncrypted;
    
    std::vector<AttendanceT> AttendanceT_list;

    Tree to_tree() const {
        Tree pt;
        pt.put("TokenNo",     TokenNo);
        pt.put("CPUID",       CPUID);
        pt.put("CommandID",   CommandID);
        pt.put("IsEncrypted", IsEncrypted);

        Tree CommandString;

        for (auto& obj : AttendanceT_list) 
            CommandString.push_back({ "", obj.to_tree() });

        pt.put("CommandString", to_string(CommandString));

        return pt;
    }
};

int main()
{
    std::vector<AttendanceT> list = {
        { "97", "99999999", "XY", "0154400000", "14042015", "1835", "I", "55", "87", "90" },
        { "87", "99999998", "XX", "0154300000", "15052015", "1947", "O", "54", "89", "91" },
    };

    POST3 obj { "ABC123456", "ABC123456", "09", "0", list };

    std::cout << to_string(obj.to_tree());
}
