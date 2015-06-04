#include <iostream>
using namespace std;
class complex
{
private:
  double x, y;
public:
  complex(double _x, double _y)
    :x(_x), y(_y)
  {}
  double getX() const {return x;}
  double getY() const {return y;}
  friend complex operator++(complex&);
  friend complex operator++(complex&, int);    
};

//Preincrement
complex operator++(complex& inn)
{
  inn.x+=1.0;
  inn.y+=1.0;
  return inn;
}

//Postincrement
complex operator++(complex& inn, int)
{
  complex xx(inn.x, inn.y);
  ++inn;
  return xx;
}

ostream& operator<<(ostream& cout, const complex& cc)
{
  cout<<cc.getX()<<" + "<<cc.getY()<<"i";
  return cout;
}

int main()
{
  complex c1(1.0, 2.0);
  cout<<c1<<endl;
  cout<<++c1<<endl;
  cout<<c1++<<endl;
  cout<<c1<<endl;
 
  return 0;
}
