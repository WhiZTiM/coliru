#include <iostream>

struct Dimension
{
    std::size_t width {800ULL};
    std::size_t height {600ULL};
};

struct Preferences
{
    friend class A;
public:
    Preferences() = default;

    template<class ...T>
    Preferences(T... t)
    { init(t...); }
private:
    template<class ...T>
    void init(Dimension d, T... t)
    { this->d = d; init(t...); }

    template<class ...T>
    void init(std::string s, T... t)
    { this->s = s; init(t...); }

    void init()
    {  }
private:
    Dimension d {800ULL, 600ULL};
    std::string s {"hello world"};
    //...
};

class A
{
public:
    template<class ...T>
    A(T... t) : pref(t...)
    {std::cout << pref.d.width << "\t" << pref.d.height << "\t" << pref.s << std::endl;}
private:
    Preferences pref;
};

int main()
{
    A a(Dimension{1ULL, 2ULL}, std::string("3, 4, 5"));
    A b(std::string("3, 4, 5"), Dimension{1ULL, 2ULL});
    
    return 0;
}