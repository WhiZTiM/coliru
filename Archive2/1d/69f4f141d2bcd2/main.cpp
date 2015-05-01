#include <iostream>
class C {
    int a,b;
    public:
        int get_a(){
            return a;
        }
        int get_b(){
            return b;
        }
        
        C(int _a, int _b):
        a(_a), b(_b)
        {}
};
int main(){
    C c{3,6};
    std::cout<<c.get_a()<<'\n';
    std::cout<<c.get_b()<<'\n';
    return 0;
}