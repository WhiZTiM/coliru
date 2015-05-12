#include <type_traits>
#include <iostream>

template <class B>
typename std::enable_if < std::is_same<B,int>::value ||std::is_same<B,double>::value || std::is_same<B,std::string>::value ,std::string   >::type
 add (std::string str , B b){
 return str + std::to_string(b);    
}

template <class B>
typename std::enable_if < std::is_same<B,int>::value ||std::is_same<B,double>::value || std::is_same<B,std::string>::value ,std::string   >::type
 add (B b, std::string str){
 return std::to_string(b)+ str ;    
}

template <class A , class B>
typename std::enable_if < (std::is_same<B,int>::value ||std::is_same<B,double>::value)&& (std::is_same<A,int>::value ||std::is_same<A,double>::value) , decltype(A()+B())  >::type
 add (B b, A a){
 return a+b;  
}


int main (void){
 std::cout << add ("hi there" , 3)<<"\n";
 std::cout << add (3 , "hi there")<<"\n";
 std::cout << add (3.14 , 2)<<"\n";
  std::cout << add (4 , 2)<<"\n";
return 0;    
}