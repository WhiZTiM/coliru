#include <iostream>
struct A{
    A(){ std::cout << "def\n"; }
	A(const A& a){ std::cout << "copy\n"; }
	A(A&& a){ std::cout << "move\n"; }
};

A f(const A& a){
	return a;
}

int main(){
	
	A a;
	A b = std::move(f(a));

}