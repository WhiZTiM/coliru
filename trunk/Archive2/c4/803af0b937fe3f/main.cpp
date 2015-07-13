#include <iostream>

using namespace std;

class ArrayElement;

class Array {
    friend class ArrayElement;
    
public:
Array():_array(new float[0]), _size(0){};
~Array() {delete[] _array;}
friend ostream &operator<<(ostream&,const Array&);
ArrayElement operator[](int index);

private:
float& access(int index) 
{
  if(index>=_size)
  {
    float* NewArray=new float[index+1];
    for(int i=0;i<_size;++i) NewArray[i]=_array[i];
    for(int i=_size;i<index+1;++i) NewArray[i]=0; 
    delete[] _array;
    _array=NewArray;
    _size=index+1;
  }
  return _array[index];
}

private:
  float *_array; // pointer to array
  int _size; // current size of array
};

class ArrayElement
{
    friend class Array;

private:
    ArrayElement(Array & array, int index) : array(array), index(index) { }
    
public:
    ArrayElement const & operator=(float v) const {
        array.access(index) = v;
        return *this;
    }
    
    ArrayElement const & operator=(ArrayElement const & other) const {
        array.access(index) = other;
        return *this;
    }
    
    operator float() const {
        return array.access(index);
    }
    
private:
    Array & array;
    int index;
};

ArrayElement Array::operator[](int index) {
    return ArrayElement(*this, index);
}

ostream &operator << ( ostream &out,  const Array& obj) // overloading operator<< to easily print array
{
  cout << "Array:\n\n";
  for (int i=0;i<obj._size;++i) 
  {
    cout << obj._array[i];
    if(i+1!=obj._size) cout << ", "; 
  }
  cout << ".\n";
  return out;
}

int main()
{
  Array CustomArray;
  CustomArray[0] = CustomArray[1] = CustomArray[2] = 3.14;
  cout << CustomArray << endl;
}