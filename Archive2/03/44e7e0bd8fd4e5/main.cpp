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
    os << typeA("Jon Skeet", 123);
    os << typeA("Bjarne Stroustrup", 456);
    istringstream is(os.str());
    typeA a1;
    is >> a1;
    std::cout << "read1: name = '" << a1.name << "', id = " << a1.id << std::endl;
    typeA a2;
    is >> a2;
    std::cout << "read1: name = '" << a2.name << "', id = " << a2.id << std::endl;
}