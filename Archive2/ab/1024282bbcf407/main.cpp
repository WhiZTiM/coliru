#include <iostream>
#include <string>

Class Level {
private:
    int size;
    float** a_predefined_2d_array;
public:
    int GetSize();
    int SetSize(int);
    int DoSomething();
    int Load(string, int);

};

int Level::GetSize() {
   return size;
}

int Level::SetSize(int _size) {
   size = _size
}

int Level::Load(string str, int _size) {
   SetSize(_size);             //works fine!
   cout<<GetSize()<<endl;      //works fine!
   //basically loads everything to initiliaze the program. The point is that the above calls work fine!
}

//The problem is here!!!
int Level::DoSomething() {
   a_predefined_2d_array = new float*[GetSize()]; //SEG FAULTS!!!
   cout<<"size = "<<GetSize()<<endl; //SEG FAULTS!!!
}