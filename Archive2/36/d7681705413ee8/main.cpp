#include <iostream>

static int a = 1;

void mutate(){
    a = 2;
}

void fun(int const& const_ref_a){
	// prints 1
	std::cout << const_ref_a << std::endl;
	mutate();
	// prints 2
	// it changed even it is const reference (reference to const int)
	std::cout << const_ref_a << std::endl;
}

int main(){
	fun(a);
}