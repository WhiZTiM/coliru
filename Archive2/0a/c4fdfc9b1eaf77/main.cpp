#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>
#include <fstream>
#include <iostream>

using boost::property_tree::ptree;

enum class YesNo { No, Yes };

static inline std::ostream& operator<<(std::ostream& os, YesNo v) {
    switch(v) {
        case YesNo::Yes: return os << "Yes";
        case YesNo::No:  return os << "No";
    }
    return os << "??";
}

struct YesNoTranslator {
    typedef std::string  internal_type;
    typedef YesNo        external_type;
 
    boost::optional<external_type> get_value(internal_type const& v) {
        if (v == "Yes") return YesNo::Yes;
        if (v == "No")  return YesNo::No;

        return boost::none;
    }

    boost::optional<internal_type> put_value(external_type const& v) {
        switch(v) {
            case YesNo::Yes: return std::string("Yes");
            case YesNo::No:  return std::string("No");
            default: throw std::domain_error("YesNo");
        }
    }
};

static YesNoTranslator trans;

int main() {

    std::ifstream ifs("input.txt"); 

    ptree pt;
    read_xml(ifs, pt);


    for (auto&& field : { "demo.positive", "demo.negative", "demo.invalid" })
    {
        try {
            std::cout << "With 'No' default: '" << field << "': " << pt.get(field, YesNo::No, trans) << "\n";
            std::cout << "Without default:   '" << field << "': " << pt.get<YesNo>(field, trans)     << "\n";
        } catch(std::exception const& e) {
            std::cout << "Error parsing '"      << field << "': " << e.what()                        << "\n";
        }
    }

}
