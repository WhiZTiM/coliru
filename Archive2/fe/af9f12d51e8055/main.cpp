#include <cassert>
#include <iostream>
#include <iterator>
#include <locale>
#include <memory>
#include <sstream>
#include <string>
#include <vector>
#include <stdexcept>

struct Holder
{
    virtual std::string   to_string() const = 0;
    virtual std::istream& read(std::istream&) = 0;
    virtual ~Holder() = default;
};
std::ostream& operator<<(std::ostream& out, const Holder& h)
{ return out << h.to_string(); }
std::istream& operator>>(std::istream& in, Holder& h)
{ return h.read(in); }

template <typename T>
struct ConcreteHolder : public Holder
{
    virtual std::string   to_string() const override;
    virtual std::istream& read(std::istream&) override;
  private:
    T value;
};
template <typename T>
std::string ConcreteHolder<T>::to_string() const
{
    std::ostringstream o;
    o << value;
    return o.str();
}
template <typename T>
std::istream& ConcreteHolder<T>::read(std::istream& in)
{
    return in >> value;
}

std::unique_ptr<Holder> getHolder(const std::string& datatype)
{
    if(datatype == "string")
        return std::make_unique<ConcreteHolder<std::string>>();
    if(datatype == "luint")
        return std::make_unique<ConcreteHolder<unsigned>>();
    throw std::logic_error("unsupported data type");
}

using row_t = std::vector<std::unique_ptr<Holder>>;

row_t parse(const std::vector<std::string>& types, std::istream& data)
{
    row_t row;
    for(auto& s: types) {
        auto p = getHolder(s);
        data >> *p;
        row.push_back(std::move(p));
    }
    return row;
}

struct colon_space : std::ctype<char>
{
    static const mask* make_table()
    {
        // make a copy of the "C" locale table
        static std::vector<mask> v(classic_table(), classic_table() + table_size);
        v[':'] |=  space;  // colon  will be classified as whitespace
        return &v[0];
    }
    colon_space(std::size_t refs = 0) : ctype(make_table(), false, refs) {}
};


int main()
{
    std::istringstream input(R"(tname:Accounts
                                datatypes:luint:string:string
                                columnnames:user_id:username:password
                                segmentinfo:a:5:s:6:t:7
                                1:account1:password2
                                2:ssdsad:password3
                                0:tsdasdad:passwor1)" );
    std::string temp;
    //PARSING HEADER
    std::getline(input, temp); //skip First line
    std::getline(input, temp); //read Second line
    std::istringstream row;
    row.imbue(std::locale(row.getloc(), new colon_space)); //Threat : as space.
    row.str(temp);
    row >> temp; assert(temp == "datatypes");
    std::vector<std::string> types {
        std::istream_iterator<std::string>(row),
        std::istream_iterator<std::string>()
    }; //read data types
    std::getline(input, temp); //skip Third line
    std::getline(input, temp); //skip fourth line

    //ACTUALLY READ DATA
    std::vector<row_t> data;
    while(std::getline(input, temp)) {
        row.clear();
        row.str(temp);
        data.push_back(parse(types, row));
    }

    //OUTPUT
    for(const auto& r: data) {
        for(const auto& e: r)
            std::cout << *e << ' ';
        std::cout << '\n';
    }
}
