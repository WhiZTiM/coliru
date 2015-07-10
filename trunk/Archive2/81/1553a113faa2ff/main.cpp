#include <bits/stdc++.h>
using namespace std;
void binary(int x)
{
int i=31;
while(i>=0)
{
    if(x&(1<<i))
      cout<<'1';
    else
      cout<<'0';
    i--;  
}
cout<<endl;
}
int main() {
  int i=31;
  int j=INT_MAX;
  int k=j^i;
  int g=~i;
  binary(j);
  binary(i);
  binary(k);
  binary(g);
  cout<<k<<endl<<g;
 return 0;
}