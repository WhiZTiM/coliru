#include <iostream>
using namespace std;

int main()
{
unsigned int i=0x3f800000;
float* p=(float*)(&i);
float f=*p;
cout<<f;
}