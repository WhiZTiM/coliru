#include <iostream>

using namespace std;

class RGB
{
public:

RGB(float r1, float g1, float  b1);
RGB(RGB const& color); //copy constructor
RGB();

friend ostream& operator<<(ostream& os, RGB& color);
friend istream& operator>>(istream& is, RGB& color);

friend float r();
friend float g();
friend float b();
private:
    float r, g, b;
};

//Something something

RGB::RGB(float r1, float g1, float b1 ){
r = r1;
g = g1;
b = b1;
}

//Something something

ostream& operator<<(ostream& os, RGB& color){    // << Overloading
return os<<"Red: "<<color.r<<endl<<"Green: "<<color.g<<endl<<"Blue: "<<color.b<<endl;
}

int main()
{
    RGB mycolor(1,2,3);
    cout<<mycolor;
}
