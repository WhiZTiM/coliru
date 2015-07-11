#include <iostream>
struct A{
    A(){ std::cout << "def\n"; }
	A(const A& a){ std::cout << "copy\n"; }
	A(A&& a){ std::cout << "move\n"; }
};

A&& f(A& a){
	return std::move(a);
}

int main(){
	
	A a;
	A b = f(a);

}