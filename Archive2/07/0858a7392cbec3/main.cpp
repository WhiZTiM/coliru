#include <iostream>
#include <memory>
#include"omp.h"

class A{
    public:
		A(){
#pragma omp critical
			{ std::cout<<this<<std::endl; }
		}
};

int main(){
#pragma omp parallel for 
	for(unsigned int i=0;i<4;i++){
		std::shared_ptr<A> sim(std::make_shared<A>());
	}
	for(unsigned int i=0;i<4;i++){
		std::shared_ptr<A> sim(std::make_shared<A>());
	}
#pragma omp parallel for 
	for(unsigned int i=0;i<4;i++){
		A sim;
	}
	for(unsigned int i=0;i<4;i++){
		A sim;
	}
}
