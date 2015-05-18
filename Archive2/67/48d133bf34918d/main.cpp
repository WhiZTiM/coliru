#include <iostream>
#include <string>
#include <boost/none_t.hpp>
#include <boost/variant.hpp>

using namespace std;

class a
{
public:
    a(const std::string & s) : _name(s)
    {
        cout<<"Base Constructor Called\n";
    }

    virtual ~a()
    {
        cout << _name << " : " << "Base Destructor called\n";
    }

private:
    std::string _name;
};

int main()
{
    boost::variant<int, a> v1;
    boost::variant<a, int> v2 = a("asdfas");
    boost::variant<boost::none_t, a> v3;
}
