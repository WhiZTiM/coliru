#include<list>
#include<functional>

struct A
{
   int id;
   double smth;
};

struct B
{
   int id;
   std::string name;
};

struct C
{
   int id;
   std::string name;
   double smth;
   C(A const&, B const&) {}
};

int main()
{

auto compare =  [](auto const& u, auto const& v) { return u.id < v.id;};

    std::list<A> a;
    a.sort(compare);
    std::list<B> b;
    b.sort(compare);

    std::list<C> c;
    auto ita = std::begin(a);
    auto itb = std::begin(b);
    while(ita != std::end(a) && itb != std::end(b))
    {
        if(ita->id == itb->id)
        {
            c.emplace_back(*ita, *itb);
            ++ita;
            ++itb;
        }
        else if(ita->id < itb->id)
        {
            ++ita;
        }
        else
        {
            ++itb;
        }         
    }
}