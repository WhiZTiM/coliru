#include<iostream>
#include<memory>
using namespace std;

int main(){
        auto sp = make_shared<int>();
        auto p = sp.get();
        delete ((char*)p - 16);
        cout <<"Before main function exits!"<<endl;  //which I add for debug
        return 0;
}