#include <iostream>
#include <string>
using namespace std;


string foo() {
  string foo_ret="foo string";
  return foo_ret;
}


int main(){

  string& a = foo();

}