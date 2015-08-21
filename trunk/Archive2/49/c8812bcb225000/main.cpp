enum Type { T1,T2,T3,TA };

struct A
{
   int id;
   double smth;
};

struct B
{
   int id;
   std::string name;
   Type type;
};

struct C
{
   int id;
   std::string name;
   Type type;
   double smth;
};

struct MakeC {
    C operator()(A const& a) const { return { a.id, "",     TA,     a.smth }; }
    C operator()(B const& b) const { return { b.id, b.name, b.type, 0.0    }; }
};

#include <iterator>
#include <algorithm>

int main() {
    std::vector<A> as(10);
    std::vector<B> bs(10);

    std::vector<C> cs;

    std::transform(as.begin(), as.end(), back_inserter(cs), MakeC());
    std::transform(bs.begin(), bs.end(), back_inserter(cs), MakeC());
}
