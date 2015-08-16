#include <iostream>
#include <vector>
using namespace std;

int main(){
    vector<int> v = {0,1,2,3,4,5,6,7,8,9,10};
    
    int pos = 0;
    for(int& i : v){
        cout << i << ", ";
        if(i == 5){
            v.erase(v.begin()+pos);
        }
        pos++;
    }
    cout << endl;
}
