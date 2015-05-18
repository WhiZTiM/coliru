#include<iostream>
int Divide(int val1,int val2){
    if(val2==0)
        throw 0;
    return val1/val2;
}
int main(){
    int x1=20,x2=0;
    try{
        int result=Divide(x1,x2);
        std::cout<<result<<std::endl;
    }
    catch(...){
        x2=1;
        std::cout<<Divide(x1,x2)<<std::endl;
    }
    return 0;
}