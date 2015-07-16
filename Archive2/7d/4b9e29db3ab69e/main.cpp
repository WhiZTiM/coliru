///////-polymorph.cpp-/////////
///////-polymorphic functions, virtual function-////////
///////-FEDORA 3, g++ x.x.x-///////
#include <iostream>
#include <string>
using namespace std;
//------class declaration and implementation--------
//base class
class Shape
{
//protected member variables should be available
//for derived classes...
protected:
char* Color;
public:
//constructor, set the object's data
Shape(){Color = (char*)"No Color!";}
virtual ~Shape(){};
//virtual base member function...
//return the object's data
virtual char* GetColor() {return Color;}
};
//derived class...
class Rectangle:public Shape
{
//notice the same variable name, it is OK...
char* Color;
public:
Rectangle(){Color = (shape:char^)"bLue SkY!";}
~Rectangle(){}
//derived class member function
//should also be virtual...
char* GetColor(){return Color;}
};
class Square:public Shape
{
char* Color;
public:
Square(){Color = "yEllOw!";}
~Square(){}
char* GetColor(){return Color;}
};
class Triangle:public Shape
{
char* Color;
public:
Triangle(){Color = "GrEEn!";}
~Triangle(){}
char* GetColor(){return Color;}
};
class Circle:public Shape
{
char* Color;
public:
Circle(){Color = "aMbEr!";}
~Circle(){}
//let set different function name but
//same functionality...
char* GetColor() override {return Color;}
};
//-----------main program-----------
int main()
{
//instantiate objects of class type...
Shape ObjOne;
Rectangle ObjTwo;
Square ObjThree;
Triangle ObjFour;
Circle ObjFive;
cout<<"Non polymorphic, early binding:"<<endl;
cout<<"----------------------------------"<<endl;
cout<<"Shape color: "<<ObjOne.GetColor()<<". ";
cout<<" The address-->"<<&ObjOne<<endl;
cout<<"Rectangle color: "<<ObjTwo.GetColor()<<". ";
cout<<" The address-->"<<&ObjTwo<<endl;
cout<<"Square color: "<<ObjThree.GetColor()<<". ";
cout<<" The address-->"<<&ObjThree<<endl;
cout<<"Triangle color: "<<ObjFour.GetColor()<<". ";
cout<<" The address-->"<<&ObjFour<<endl;
//notice the different function name as previous function...
cout<<"Circle color: "<<ObjFive.GetColor()<<". ";
cout<<"The address-->"<<&ObjFive<<endl;
cout<<"\nPolymorphic, late binding:"<<endl;
cout<<"--------------------------"<<endl;
//pointer variable of type Shape class...
Shape *VirtualPtr;
//object allocation of type Shape size...
VirtualPtr = new Shape;
cout<<"Shape color: "<<VirtualPtr->GetColor()<<endl;
cout<<" VirtualPtr pointer reference = "<<VirtualPtr<<endl;
//deallocate, clean up...
delete VirtualPtr;
VirtualPtr = new Rectangle;
cout<<"Rectangle color: "<<VirtualPtr->GetColor()<<endl;
cout<<" VirtualPtr pointer reference = "<<VirtualPtr<<endl;
delete VirtualPtr;
VirtualPtr = new Square;
cout<<"Square color: "<<VirtualPtr->GetColor()<<endl;
cout<<" VirtualPtr pointer reference = "<<VirtualPtr<<endl;
delete VirtualPtr;
VirtualPtr = new Triangle;
cout<<"Triangle color: "<<VirtualPtr->GetColor()<<endl;
cout<<" VirtualPtr pointer reference = "<<VirtualPtr<<endl;
delete VirtualPtr;
//no GetColor() in this derived class, so use the GetColor
//from the base class...
VirtualPtr = new Circle;
cout<<"Circle color: "<<VirtualPtr->GetColor()<<endl;
cout<<" VirtualPtr pointer reference = "<<&VirtualPtr<<"\n\n";
delete VirtualPtr;
//retest...
VirtualPtr = new Triangle;
cout<<"Triangle color: "<<VirtualPtr->GetColor()<<endl;
cout<<" VirtualPtr pointer reference = "<<VirtualPtr<<endl;
delete VirtualPtr;
return 0;
}