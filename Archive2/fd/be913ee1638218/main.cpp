#include <iostream>
#include <string>
#include <vector>
#include <stdlib.h>
#include <memory.h>
#include <ctime>

using namespace std;

class MyString { 
 private: 
  char* m_data; 
  size_t   m_len; 
  void copy_data(const char *s) { 
    m_data = new char[m_len+1]; 
    memcpy(m_data, s, m_len); 
    m_data[m_len] = '\0'; 
  } 
 public: 
  MyString() { 
    m_data = NULL; 
    m_len = 0; 
  } 

  MyString(const char* p) { 
    m_len = strlen (p); 
    copy_data(p); 
  } 


MyString(MyString&& str) { 
   // std::cout << "Move Constructor is called! source: " << str.m_data << std::endl; 
    m_len = str.m_len; 
    m_data = str.m_data; //避免了不必要的拷贝
    str.m_len = 0; 
    str.m_data = NULL; 
 }
 
 
 MyString& operator=(MyString&& str) { 
    //std::cout << "Move Assignment is called! source: " << str.m_data << std::endl; 
    if (this != &str) { 
      m_len = str.m_len; 
     m_data = str.m_data; //避免了不必要的拷贝
      str.m_len = 0; 
      str.m_data = NULL; 
    } 
    return *this; 
 }


  virtual ~MyString() { 
    if (m_data) free(m_data); 
  } 
 }; 


int main() { 
  MyString a;
  int N=50000000;
  clock_t start, end, time;
  
  start = clock();
  for(int i=0;i<N;i++)
  {
  a = MyString("Hello"); 
  std::vector<MyString> vec; 
  vec.push_back(MyString("World")); 
  }
  end = clock();
  
  time = (double)(end - start) /  CLOCKS_PER_SEC ;
  
  printf("%d round ,get time %f\n",N,(double)time);
  return 0;
 }