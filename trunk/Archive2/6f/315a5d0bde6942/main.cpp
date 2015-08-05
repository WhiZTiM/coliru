#include <tuple>
#include <iostream>
using namespace std;
const int width  = 2;
const int height = 2;
struct O {};
struct X {};
// starting level
using start = tuple<
                    O, O,
                    O, O
                    >;
/////////PRINT/////////
template<typename T>
void print();
template<>
void print<O>(){
    cout<<"O"<<endl;
}
template<>
void print<X>(){
    cout<<"X"<<endl;
}
//////////////////////
template<typename tuple,int N>
struct Printer{
    static void print_tuple(){
        Printer<tuple,N-1>::print_tuple();
        if(N % width == 0)
            cout<<endl;
        print<typename tuple_element<N,tuple>::type>();
    }
};
template<typename tuple>
struct Printer<tuple,0>{
    static void print_tuple(){
        print<typename  tuple_element<0,tuple>::type>();
    }
};

int main(int argc,char *argv[]){
    Printer<start,3>::print_tuple();
return 0;
}


