#include<iostream>
#include<string>
#include<regex>

using namespace std;

int main()
{
 

  regex pattern("(.+) def");
  smatch a;
  string s = "pqr def";
  regex_search(s, a, pattern);
  cout << a[1] << ";";

}