#include<iostream>
#include<fstream>
#include<vector>
#include<sstream>
#include<string>
#include<iterator>
#include<regex>

using namespace std;

int main()
{
 

  regex pattern("(.+) def");
  smatch a;
  string s = "pqr def";
  regex_search(s, a, pattern);
  cout << a.size() << a[1] << ";";

}