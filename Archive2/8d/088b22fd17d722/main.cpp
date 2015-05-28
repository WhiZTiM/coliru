// Example program
#include <iostream>
#include <string>
#include <vector>

using std::cout;

class Object1
{
public:
  int value1;
  int value2;

  Object1() : value1(0), value2(1)
  {
    std::cout << "\n Object1()..";
  }

  Object1(int x) : value1(x), value2(1)
  {
    std::wcout << "\n Object1(int "<< x <<")..";
  }

  Object1(const Object1 & that)
    : value1(that.value1), value2(that.value2)
  {
    std::wcout << "\n Object1 (Object1 & that)..";
  }
  
  // move constructor
  Object1(Object1 && temp)
    : value1(temp.value1), value2(temp.value2)
  {
    std::cout << "\n Object1 (Object1 && temp).., temp.value1 = "<< temp.value1;
    temp.value2 = 0;
  }
  
  Object1& operator=(const int v)
  {
    std::cout << "\n Object1& operator=(const int "<< v << ")..";
    value1 = v;
    return *this;
  }


  Object1& operator=(const Object1 & v)
  {
    std::cout << "\n Object1& operator=(const Object1 &v).. v = "<< v.value1;
    if (this != &v)
    {
      value1 = v.value1;
      value2 = v.value2;
    }
    else
      std::cout << "\n \t if (this == &v)";
    return *this;
  }

  // move assignment operator
  Object1 & operator=(Object1 && temp)
  {
    //__mtt_assert(this != &temp); // assert if this is not a temporary

    std::cout << "\n Object1 & operator=(Object1 && temp)..,temp.value1 =  "<< temp.value1;
    
    std::swap(value1, temp.value1);
    std::swap(value2, temp.value2);
    return *this;
  }


  ~Object1()
  {
    if (value2)
      std::cout << "\n ~Object1().. for " << value1;
    else
      std::cout << "\n ~Object1() canceled!!!...for " << value1;
  }

};

std::ostream & operator<< (std::ostream & os, const Object1& x)
{
    os << x.value1;
    return os;
}




int main()
{
  std::string name;
  std::cout << "What is your name? ";
  /*
  getline (std::cin, name);
  std::cout << "Hello, " << name << "!\n";
  */
  
  std::vector<Object1> ov(10);
  ov.reserve(15);
  ov.resize(10);
  
  //cout <<"\n start ...";
  
  for (unsigned int i =0; i < 10; ++i)
    //ov.push_back((int)i);
    ov[i] = i;
  
  cout <<"\n\n";
  for (unsigned int i =0; i < ov.size(); ++i)
    cout << ov[i] <<", "; 
  
  ov.insert(ov.begin() + 5, ov.begin() + 3, ov.begin() + 6);
  
  cout <<"\n\n";
  for (unsigned int i =0; i < ov.size(); ++i)
    cout << ov[i] <<", ";
    
}
