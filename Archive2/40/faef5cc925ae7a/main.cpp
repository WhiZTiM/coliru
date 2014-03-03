#include <map>
#include <sstream>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/serialization/serialization.hpp>
#include <boost/serialization/map.hpp>

struct Demo
{
    int i;
    std::string truth;

    using Vars = std::map<std::string, double>;
    Vars vars;

    template <typename Archive> void serialize(Archive& ar, unsigned /*version*/)
    {
        ar & i;
        ar & truth;
        ar & vars;
    }

    friend std::ostream& operator<<(std::ostream& os, Demo const& demo)
    {
        os << demo.i << ';' << demo.truth << ";";
        for (auto& e : demo.vars)
            os << e.first << ";" << e.second << ";";
        return os;
    }
};

static std::string serialize(Demo const& data)
{
    std::ostringstream oss;
    boost::archive::text_oarchive oa(oss);
    oa << data;
    return oss.str();
}

static Demo deserialize(std::string const& text)
{
    std::istringstream iss(text);
    boost::archive::text_iarchive ia(iss);
    Demo data;
    ia >> data;
    return data;
}

int main()
{
    Demo a { 42, "LtUaE", { { "PI", 3.1415926 }, { "e", std::exp(1.0) } } };
    std::cout << "Debug : " << a << "\n";

    std::string const serialized = serialize(a);
    std::cout << "Serious serialization: " << serialized << "\n";

    // to parse back:
    Demo roundtrip = deserialize(serialized);
    std::cout << "Parsed back: " << roundtrip << "\n";
}
