#include<iostream>

int main(){
  char p='0';
  char* ptr=&p;
  std::cout<<"This is the pointer: "<<&ptr<<" ---"<<*ptr <<"----"<<ptr;
return 0;
}  