#include <iostream>
#include <fstream>

class fooprint
{
    private:
    std::ostream *os;
    
    public:
    fooprint(std::ostream &out = std::cout) : os(&out) {}
    ~fooprint() { *os << std::endl;}
    
    template<class T>
    fooprint &operator, (const T output)
    {
        *os << output << ' ';
        return *this;
    }
};

#define print      fooprint(),
#define write(out) fooprint(out),

int main()
{
    double a = 2.0;
    print "Hello", "World!";
    print "value of a =", a;
    print a;

    ////////// This code won't compile with g++
    /*
    std::ofstream data("tmp.txt");
    write(data) "writing to tmp";
    write(data) a;
    data.close();
    */
    return 0;
}
