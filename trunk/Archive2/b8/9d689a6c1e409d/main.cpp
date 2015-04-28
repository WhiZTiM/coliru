#include <vector>
#include <iterator>
#include <iostream>
#include <sstream>

using namespace std;

class typeA
{  
public:
    string name; //the name is multiple words
    int id;
public:
    typeA(string name, int id): name(name), id(id){}
    typeA(){}

    friend ostream& operator <<(ostream& out, const typeA& a)
    {
        out << a.name << '\n';
        out << a.id << '\n';
        return out;
    }
    
    friend istream& operator >>(istream& in, typeA& a)
    {
        getline(in, a.name); // since the name is first and last i have to use getline
        in >> a.id;
        in.ignore();
        return in;
    }
};

int main()
{
    ostringstream os;
    os << typeA("James Hetfield", 123);
    os << typeA("Lars Ulrich", 456);
    os << typeA("Kirk Hammett", 789);
    istringstream is(os.str());
    
    for (int i = 0; i < 3; ++i) {
        typeA a;
        is >> a;
        std::cout << "read " << i << ": name = '" << a.name << "', id = " << a.id << std::endl;
    }
}