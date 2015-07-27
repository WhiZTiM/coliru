#include <iostream>
#include <string>
#include <vector>
using namespace std;

class HasPtr{
 public:
    //constructor accepts a string
    HasPtr(const string &s = string()) : ps(new string(s)), i(0), use(new size_t(1)) {}  
    //copy constructor
    HasPtr(const HasPtr &h) : ps(h.ps), i(h.i), use(h.use) { ++*use; }
    //copy assignment operator 
    HasPtr &operator=(const HasPtr &h)
    {
        ++*h.use;
        if(--*use == 0)
        {
            delete ps;
            delete use;
        }
        ps = h.ps;
        i = h.i;
        use = h.use;

        return *this;
    }
    void modify(const string& s) {
        *ps = s;
    }
    ~HasPtr()
    {
        if(--*use == 0)
        {
            delete ps;
            delete use;
        }
    }

//private:
    string *ps;
    int i;

    size_t *use;
};


int main()
{
    HasPtr h("hi mom");
    HasPtr h2 = h;
    HasPtr h3("hi dad");
    //h2 = h3;
    h2.modify(*h3.ps);

    cout << "h: " << *h.ps << endl;
    cout << "h2: " << *h2.ps << endl;
    cout << "h3: " << *h3.ps << endl;
}