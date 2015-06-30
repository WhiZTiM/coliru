#include <sstream>
#include <string>
#include <vector>
#include <map>
#include <iostream>

#include <boost/algorithm/string.hpp>

class CONTRACT_DESC {
    public:
    CONTRACT_DESC() = default;

    // Assume the members require copying into.
    CONTRACT_DESC(
        std::string const& instrument_name,
        std::string const& symbol,
        int expiry_date,
        int strike_price,
        std::string option_type) :
        _instrument_name(instrument_name),
        _symbol(symbol),
        _expiry_date(expiry_date),
        _strike_price(strike_price),
        _option_type(option_type) {}

private:
    std::string _instrument_name;
    std::string _symbol;
    int _expiry_date;
    int _strike_price;
    std::string _option_type;
    int _ca_level;
};

auto input = 
"35000|26009|OPTIDX|BANKNIFTY|XX||1119709800|1950000|CE|1|0|0|0|0|1|1||2|0||2|0||3|0||1112140800|0|1119709800|0|25|25|5|9.99999999999000E+11|2.50100000000000E+03|0.00000000000000E+00|1112140800|0|0|0|0|0|5|15670|0|0|0|1117903669|1119657600|1119709800|15|1||BANKNIFTY15JUN19500CE|0|0|0|0||E|N|N|N||N|||1975|N\n"
"35001|26009|OPTIDX|BANKNIFTY|XX||1119709800|1950000|PE|1|0|0|0|0|1|1||2|0||2|0||3|0||1112140800|0|1119709800|0|25|25|5|9.99999999999000E+11|2.50100000000000E+03|0.00000000000000E+00|1112140800|0|0|0|0|0|53210|295630|0|0|0|1117903669|1119657600|1119709800|15|1||BANKNIFTY15JUN19500PE|0|0|0|0||E|N|N|N||N|||174420|N\n"
"134584|0|||||0|0||0|0|0|0|0|0|0||0|0||0|0||0|0||0|0|0|0|0|0|0|0.00000000000000E+00|0.00000000000000E+00|0.00000000000000E+00|0|0|0|0|0|0|0|0|0|0|0|1117903969|0|0|15|0|||0|0|0|0||E|N|N|N||N|||0|Y\n"
"134585|0|||||0|0||0|0|0|0|0|0|0||0|0||0|0||0|0||0|0|0|0|0|0|0|0.00000000000000E+00|0.00000000000000E+00|0.00000000000000E+00|0|0|0|0|0|0|0|0|0|0|0|1117903969|0|0|15|0|||0|0|0|0||E|N|N|N||N|||0|Y\n"
"35002|26009|OPTIDX|BANKNIFTY|XX||1119709800|1960000|CE|1|0|0|0|0|1|1||2|0||2|0||3|0||1112140800|0|1119709800|0|25|25|5|9.99999999999000E+11|2.50100000000000E+03|0.00000000000000E+00|1112140800|0|0|0|0|0|5|13440|0|0|0|1117903669|1119657600|1119709800|15|1||BANKNIFTY15JUN19600CE|0|0|0|0||E|N|N|N||N|||1430|N\n"
"35003|26009|OPTIDX|BANKNIFTY|XX||1119709800|1960000|PE|1|0|0|0|0|1|1||2|0||2|0||3|0||1112140800|0|1119709800|0|25|25|5|9.99999999999000E+11|2.50100000000000E+03|0.00000000000000E+00|1112140800|0|0|0|0|0|58680|304470|0|0|0|1117903669|1119657600|1119709800|15|1||BANKNIFTY15JUN19600PE|0|0|0|0||E|N|N|N||N|||181575|N\n";

std::map<std::string, CONTRACT_DESC> load_contracts() {
    std::istringstream f(input);

    // No, I am not responsible for the SCREAMING_CAPS.
    std::map<std::string, CONTRACT_DESC> contracts;
    std::string line;
    std::vector<std::string> fields;
    
    // Number of columns in the CSV.
    fields.reserve(69);
    
    while(std::getline(f, line)) {
        // If last character of line is 'Y', it means the record is deleted, don't bother parsing.
        if (line.size() > 1 && line[line.size() - 1] == 'Y') {
            continue;
        }
    
        fields.clear();
        boost::split(fields, line, boost::is_any_of("|"));
    
        contracts.emplace(std::piecewise_construct,
            std::forward_as_tuple(std::move(fields[0])),
            // Can't move those.
            std::forward_as_tuple(
                fields[2],
                fields[3],
                std::stoi(fields[6]),
                std::stoi(fields[7]),
                fields[8]
            ));
    }
    
    return contracts;
}

int main() {
    auto contracts = load_contracts();
    std::cout << "That's " << contracts.size() << " records, 4 the record" << std::endl;
}