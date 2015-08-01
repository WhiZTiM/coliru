#include <iostream>
using namespace std;

class test{
public:

    test(){
        cout<<endl<<"TEST";
    }
    
    void another(){
        // cout<<endl<<"Another";
    }
    
    test(const test&) {
      cout << endl << "copy ctor";
    }

};

int main(){

    test chk = chk;
    chk.another();
 
}