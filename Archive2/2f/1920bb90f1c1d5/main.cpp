#include <iostream>
#include <memory>

int main (){
    
    int i = 1;
    while (i = 1){
        std::cout<<"I BROKE YOU!!!\n";
    }
    auto s = std::make_shared<int>(12);
    std::cout<<*s;
	return 0 ;
}