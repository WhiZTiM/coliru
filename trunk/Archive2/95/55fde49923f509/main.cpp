#include <boost/algorithm/string.hpp>
#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <vector>

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
    int         _expiry_date;
    int         _strike_price;
    std::string _option_type;
    int         _ca_level;
};

using Map = std::multimap<std::string, CONTRACT_DESC>;

Map load_contracts(std::string const& fname) {

    Map contracts;
    std::string line;
    std::vector<std::string> fields;
    
    std::ifstream f(fname, std::ios::binary);
    while(std::getline(f, line)) {
        // If last character of line is 'Y', it means the record is deleted, don't bother parsing.
        if (line.empty() || line.back() == 'Y') {
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

Map load_contracts_ex(std::string const& fname) {

    Map contracts;
    std::string line;
    std::vector<boost::iterator_range<std::string::const_iterator> > fields;
    
    std::ifstream f(fname, std::ios::binary);
    while(std::getline(f, line)) {
        // If last character of line is 'Y', it means the record is deleted, don't bother parsing.
        if (line.empty() || line.back() == 'Y') {
            continue;
        }
    
        fields.clear();

        iter_split(fields, line, token_finder(boost::is_from_range('|', '|')));

        contracts.emplace(std::piecewise_construct,
            std::forward_as_tuple(std::string { fields[0].begin(), fields[0].end() }),
            // Can't move those.
            std::forward_as_tuple(
                std::string { fields[2].begin(), fields[2].end() },
                std::string { fields[3].begin(), fields[3].end() },
                std::stoi(&*fields[6].begin()),
                std::stoi(&*fields[7].begin()),
                std::string { fields[8].begin(), fields[8].end() }
            ));
    
    }
    
    return contracts;
}

int main() {
#if 1
    auto contracts = load_contracts_ex("input.txt");
#else
    auto contracts = load_contracts("input.txt");
#endif
    std::cout << "That's " << contracts.size() << " records, 4 the record" << std::endl;
}
