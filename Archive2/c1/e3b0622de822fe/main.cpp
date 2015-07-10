#include <iostream>
#include <set>

using std::ostream;
using std::string;
class AB
{
   friend  bool compare_values (const AB&a, const AB&b);
   friend AB operator+(const AB&,const AB&);
   friend ostream& operator<<(ostream&,const AB&);
   protected:
   std::string mm;
   private:
    int j;
    int k;
    public:
    AB(int m=0,int n=0):j(m),k(n)
    {
        
    }
};
AB operator+(const AB& rhs1, const AB& rhs2)
{
    AB sum;
    sum.j=rhs1.j+rhs2.j;
    sum.k=rhs1.k+rhs2.k;
    return sum;
}

ostream& operator<<(ostream& os,const AB& obj)
{
    os<<obj.j<<" "<<obj.k;
    return os;
}

class BC: private AB
{public:
using AB:: mm;
    
};

bool compare_values (const AB&a, const AB&b)
{
    return a.j<b.j;
}
using functype=bool(*)(const AB&, const AB&);
int main()
{
   std::cout << "Hello World" << std::endl; 
   std::set<std::string,functype> mymap(&compare_values);
   AB a(0,5);
   AB b(3,8);
   std::cout<<a<<std::endl;
   BC ml;
   ml.mm="lol";
   return 0;
}
