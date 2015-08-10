#include <map>
#include <iostream>

struct X
{
    int id;
    int subId;
};

bool operator<(const X& x1, const X& x2) { return x1.id < x2.id || (x1.id == x2.id && x1.subId < x2.subId); }

struct Details {};

struct Y
{
    int getId() const { return 1; } 
    int getSubId() const { return 2; }
};

bool operator<(const X& x, const Y& y) { return x.id < y.getId() || (x.id == y.getId() && x.subId < y.getSubId()); }
bool operator<(const Y& y, const X& x) { return y.getId() < x.id || (y.getId() == x.id && y.getSubId() < x.subId); }

int main()
{
    std::map<X, Details, std::less<>> detailsMap{ {{1,1}, Details{}}, {{1,2}, Details{}} };
    Y y;
    std::cout << detailsMap.count(y);
}
