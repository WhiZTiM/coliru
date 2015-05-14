#include <string>
#include <vector>
#include <iostream>
using namespace std;
int main(){
  int ironic[2]= {0,1};
  vector<string> values;
  values.push_back("rain on your wedding day");
  values.push_back("free ride when you already paid");
  for(int it:ironic){
     cout << "It's like " << values[it] << endl;
  }
}